using System.Threading.RateLimiting;

namespace EdtWebSockEDT.RateLimiters;

public sealed class LastInQueueRateLimiter : RateLimiter
{
    private readonly object _lock = new();
    private readonly TimeSpan _waitTimeBetween;

    private TaskCompletionSource? _tcs;
    private DateTime _previousCompletion;

    private static int _currentTicketNumber = 0;

    public LastInQueueRateLimiter(
        TimeSpan waitTimeBetween)
    {
        _waitTimeBetween = waitTimeBetween;
    }

    public override TimeSpan? IdleDuration => null;

    public override RateLimiterStatistics? GetStatistics() => null;

    protected override async ValueTask<RateLimitLease> AcquireAsyncCore(int permitCount, CancellationToken cancellationToken)
    {
        if (permitCount > 1)
        {
            throw new ArgumentException("Permit count can only be 1");
        }

        int ticketNumber;
        Task waitTask;

        lock (_lock)
        {
            if (_tcs == null)
            {
                return AllowThrough();
            }
            else
            {
                ticketNumber = ++_currentTicketNumber;
            }

            waitTask = _tcs.Task;
        }

        var diff = DateTime.UtcNow - _previousCompletion;
        if (diff < _waitTimeBetween)
        {
            await Task.Delay(diff, cancellationToken);
        }

        await waitTask;

        // no new calls are waiting
        if (ticketNumber == _currentTicketNumber)
        {
            lock (_lock)
            {
                return AllowThrough();
            }
        }
        else
        {
            return Bounce();
        }

        RateLimitLease AllowThrough()
        {
            _tcs = new();
            _previousCompletion = DateTime.UtcNow;
            return new OneAtTheTimeRateLimitLease(true, _tcs);
        }

        static OneAtTheTimeRateLimitLease Bounce()
        {
            return new OneAtTheTimeRateLimitLease(false, new());
        }
    }

    protected override RateLimitLease AttemptAcquireCore(int permitCount)
    {
        throw new NotSupportedException("Only async flow is allowed");
    }

    private sealed class OneAtTheTimeRateLimitLease : RateLimitLease
    {
        private readonly TaskCompletionSource _tcs;

        public OneAtTheTimeRateLimitLease(
            bool isAcquired,
            TaskCompletionSource tcs)
        {
            IsAcquired = isAcquired;
            _tcs = tcs;
        }

        public override bool IsAcquired { get; }

        public override IEnumerable<string> MetadataNames => [];

        public override bool TryGetMetadata(string metadataName, out object? metadata)
        {
            metadata = null;
            return false;
        }

        protected override void Dispose(bool disposing)
        {
            _tcs.SetResult();
        }
    }
}
