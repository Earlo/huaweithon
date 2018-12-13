namespace HuaweiARUnitySDK
{
    using System;
    using HuaweiARInternal;
    using UnityEngine;

    public class ARAnchor
    {
        internal  IntPtr m_anchorHandle = IntPtr.Zero;
        private NDKSession m_ndkSession;
        //this method must be called in ARAnchorMaager
        internal ARAnchor(IntPtr anchorHandle,NDKSession session)
        {
            m_anchorHandle = anchorHandle;
            m_ndkSession = session;
        }

        public Pose GetPose()
        {
            return m_ndkSession.AnchorAdapter.GetPose(m_anchorHandle);
        }

        [Obsolete]
        public Pose GetPoseInUnity()
        {
            return GetPose();
        }
        public ARTrackable.TrackingState GetTrackingState()
        {
            return m_ndkSession.AnchorAdapter.GetTrackingState(m_anchorHandle);
        }

        public void Detach()
        {
            m_ndkSession.AnchorManager.RemoveAnchor(this);
            m_ndkSession.AnchorAdapter.Detach(m_anchorHandle);
        }

        public override bool Equals(object obj)
        {
            if (obj != null && obj is ARAnchor)
            {
                ARAnchor other = (ARAnchor)obj;
                return m_anchorHandle==other.m_anchorHandle;
            }
            else
            {
                return false;
            }
        }
        public override int GetHashCode()
        {
            return m_anchorHandle.ToInt32();
        }


        ~ARAnchor()
        {
            //release resouce here
            m_ndkSession.AnchorManager.RemoveAnchor(this);
            m_ndkSession.AnchorAdapter.Release(m_anchorHandle);
        }
    }
}
