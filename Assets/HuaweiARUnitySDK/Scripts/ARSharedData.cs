namespace HuaweiARUnitySDK
{
    using System;
    using System.Runtime.InteropServices;
    public class ARSharedData
    {
        public ARRawData RawData { get; private set; }

        internal ARSharedData(ARRawData rawData)
        {
            RawData = rawData;
        }

        public class ARRawData
        {
            public long DataSize;
            public long DataCapacity { get; private set; }
            public byte[] Data { get; private set; }
            private GCHandle m_gcHandle;
            internal IntPtr m_pinAddr { get; private set; }
            public ARRawData(long capacity)
            {
                DataCapacity = capacity;
                Data = new byte[DataCapacity];
                m_gcHandle = GCHandle.Alloc(Data, GCHandleType.Pinned);
                m_pinAddr = m_gcHandle.AddrOfPinnedObject();
            }

            ~ARRawData()
            {
                m_gcHandle.Free();
            }
        }
    }
}
