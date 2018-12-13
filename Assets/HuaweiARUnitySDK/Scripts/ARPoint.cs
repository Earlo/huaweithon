namespace HuaweiARUnitySDK
{
    using System;
    using HuaweiARInternal;
    using UnityEngine;
    using System.Collections.Generic;

    public class ARPoint: ARTrackable
    {
        public enum OrientationMode
        {
            INITIALIZED_TO_IDENTITY =0,ESTIMATED_SURFACE_NORMAL =1,
        }


        internal ARPoint(IntPtr trackableHandle, NDKSession session) : base(trackableHandle, session) { }

        public Pose GetPose()
        {
            return m_ndkSession.PointAdapter.GetPose(m_trackableHandle);
        }
        
        public OrientationMode GetOrientationMode()
        {
            return m_ndkSession.PointAdapter.GetOrientationMode(m_trackableHandle);
        }
    }
}
