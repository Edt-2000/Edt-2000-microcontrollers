namespace Core;

public interface IStatusReporter
{
    void ReportStatus(string device, bool isOk);
}
