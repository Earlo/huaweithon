namespace HuaweiARUnitySDK
{
    using HuaweiARInternal;
    using System;
    using UnityEngine;
    using System.Collections.Generic;

    public class ARHitResult
    {
        private NDKSession m_ndkSession;
        internal IntPtr m_hitResultHandle;

        internal ARHitResult(IntPtr hitResultHandle,NDKSession session)
        {
            m_hitResultHandle = hitResultHandle;
            m_ndkSession = session;
        }

        ~ARHitResult()
        {
            if (m_hitResultHandle != IntPtr.Zero)
            {
                m_ndkSession.HitResultAdapter.Destroy(m_hitResultHandle);
            }
        }
        
        public Pose HitPose
        {
            get
            {
               return  m_ndkSession.HitResultAdapter.GetHitPose(m_hitResultHandle);
            }
        }
        public float Distance
        {
            get
            {
                return m_ndkSession.HitResultAdapter.GetDistance(m_hitResultHandle);
            }
        }

        public ARTrackable GetTrackable()
        {
            return m_ndkSession.HitResultAdapter.AcquireTrackable(m_hitResultHandle);
        }
        public ARAnchor CreateAnchor()
        {
            return m_ndkSession.HitResultAdapter.AcquireNewAnchor(m_hitResultHandle);
        }


        [Obsolete]
        public Pose PoseInUnity { get { return HitPose; } }
    }
}
