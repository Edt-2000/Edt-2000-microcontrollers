using System.Threading.RateLimiting;

namespace EdtWebSockEDT.RateLimiters;

public sealed class AllowAllRateLimiter : RateLimiter
{
    private readonly RateLimitLease _lease = new AllowAllRateLimitLease();

    public override TimeSpan? IdleDuration => null;

    public override RateLimiterStatistics? GetStatistics() => null;

    protected override ValueTask<RateLimitLease> AcquireAsyncCore(int permitCount, CancellationToken cancellationToken) => new ValueTask<RateLimitLease>(_lease);

    protected override RateLimitLease AttemptAcquireCore(int permitCount) => _lease;

    private sealed class AllowAllRateLimitLease : RateLimitLease
    {
        public override bool IsAcquired => true;

        public override IEnumerable<string> MetadataNames => [];

        public override bool TryGetMetadata(string metadataName, out object? metadata)
        {
            metadata = null;
            return false;
        }
    }
}
