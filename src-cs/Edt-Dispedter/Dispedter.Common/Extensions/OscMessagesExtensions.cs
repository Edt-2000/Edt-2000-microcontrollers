using System.Collections.Generic;
using System.Linq;
using Dispedter.Common.OSC;

namespace Dispedter.Common.Extensions
{
    public static class OscMessagesExtensions
    {

        private static int _chunkSize = 30;

        public static IEnumerable<OscPacket> OptionallyBundle(this IEnumerable<OscMessage> messages)
        {
            var allMessages = messages.ToList();

            if (allMessages.Count > 1)
            {
                do
                {
                    var chunk = allMessages.Take(_chunkSize);
                    if (!chunk.Any())
                    {
                        break;
                    }

                    yield return new OscBundle(1, chunk.ToArray());

                    allMessages = allMessages.Skip(_chunkSize).ToList();
                }
                while (true);
            }
            else if (allMessages.Count == 1)
            {
                yield return allMessages[0];
            }
        }
    }
}
