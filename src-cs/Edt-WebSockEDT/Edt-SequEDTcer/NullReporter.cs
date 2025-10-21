using Core;

namespace Edt_SequEDTcer;

internal class NullReporter : IStatusReporter
{
    public void ReportStatus(string device, bool isOk) { }
}
