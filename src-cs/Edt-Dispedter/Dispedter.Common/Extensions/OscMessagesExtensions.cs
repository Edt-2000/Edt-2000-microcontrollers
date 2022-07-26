using System.Collections.Generic;
using System.Linq;
using Dispedter.Common.OSC;

namespace Dispedter.Common.Extensions
{
    public static class OscMessagesExtensions
    {
        public static OscPacket OptionallyBundle(this IEnumerable<OscMessage> messages)
        {
            return (messages.Skip(1).Any())
                ? (OscPacket)new OscBundle(1, messages.ToArray())
                : (OscPacket)messages.ElementAt(0);
        }
    }
}
