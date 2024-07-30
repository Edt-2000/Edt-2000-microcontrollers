using System.Text.Json;
using System.Text.Json.Serialization;

namespace EdtSpedtometer;

public class ValueTupleConverter<T> : JsonConverter<ValueTuple<T, T, T>>
{
    public override (T, T, T) Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
    {
        throw new NotImplementedException();
    }

    public override void Write(Utf8JsonWriter writer, (T, T, T) value, JsonSerializerOptions options)
        => JsonSerializer.Serialize<T[]>(writer, [value.Item1, value.Item2, value.Item3], options);
};
