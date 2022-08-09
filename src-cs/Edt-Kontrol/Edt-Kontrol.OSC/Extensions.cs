using System;
using System.Collections.Generic;
using System.Linq;

namespace Edt_Kontrol.OSC
{
    public static class Extensions
    {
        public static int FirstIndexAfter<T>(this IEnumerable<T> items, int start, Func<T, bool> predicate)
        {
            if (items == null)
            {
                throw new ArgumentNullException("items");
            }

            if (predicate == null)
            {
                throw new ArgumentNullException("predicate");
            }

            if (start >= items.Count())
            {
                throw new ArgumentOutOfRangeException("start");
            }

            var retVal = 0;
            foreach (var item in items)
            {
                if (retVal >= start && predicate(item))
                {
                    return retVal;
                }

                retVal++;
            }
            return -1;
        }

        public static List<List<T>> Split<T>(this IEnumerable<T> data, Func<T, bool> predicate)
        {
            var output = new List<List<T>>();
            var curr = new List<T>();
            output.Add(curr);
            foreach (var x in data)
            {
                if (predicate(x))
                {
                    curr = new List<T>();
                    output.Add(curr);
                }
                else
                {
                    curr.Add(x);
                }
            }

            return output;
        }


        public static T[] SubArray<T>(this T[] data, int index, int length)
        {
            var result = new T[length];
            Array.Copy(data, index, result, 0, length);
            return result;
        }

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

        public static IEnumerable<OscMessage> TakeRandom(this IEnumerable<OscMessage> messages, int count)
            => messages.OrderBy(x => Guid.NewGuid()).Take(count);
    }
}
