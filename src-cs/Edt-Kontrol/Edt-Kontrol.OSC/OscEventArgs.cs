using System;

namespace Edt_Kontrol.OSC
{
    public sealed class OscEventArgs
    {
        private readonly OscPacket _oscPacket;

        public OscEventArgs(OscPacket oscPacket)
        {
            _oscPacket = oscPacket;
        }

        public OscPacket GetOscPacket()
        {
            return _oscPacket;
        }
    }
}
