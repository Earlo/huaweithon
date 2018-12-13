namespace HuaweiARInternal
{
    using System;
    using UnityEngine;
    using System.Runtime.InteropServices;
    using HuaweiARUnitySDK;
    internal class ARUnityHelper
    {
        private IntPtr m_jenvHandle;
        private IntPtr m_activityHandle;
        private int m_textureId = -1;
        private const string sessionName = "com.huawei.hiar.ARSession";
        private static ARUnityHelper s_unityHelper;

        private  ARUnityHelper()
        {
            m_jenvHandle = IntPtr.Zero;
            m_activityHandle = IntPtr.Zero;
        }
        
        public static ARUnityHelper Instance
        {
            get
            {
                if (null == s_unityHelper)
                {
                    s_unityHelper= new ARUnityHelper();
                }
                return s_unityHelper;
            }
        }


        public IntPtr GetJEnv()
        {
            if(IntPtr.Zero == m_jenvHandle)
            {
                AndroidJavaClass session = new AndroidJavaClass(sessionName);
                long jEnv = session.CallStatic<long>("getJEnv");
                m_jenvHandle = new IntPtr(jEnv);
            }
            return m_jenvHandle;
        }

        public IntPtr GetActivityHandle()
        {
            AndroidJavaClass unityPlayer = new AndroidJavaClass("com.unity3d.player.UnityPlayer");
            AndroidJavaObject activity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity");
            m_activityHandle = activity.GetRawObject();
            return m_activityHandle;
        }

        public int GetTextureId()
        {
            if (m_textureId == -1)
            {
                AndroidJavaClass session = new AndroidJavaClass(sessionName);
                m_textureId = session.CallStatic<int>("getTextureId");
            }
            return m_textureId;
        }
    }
}
