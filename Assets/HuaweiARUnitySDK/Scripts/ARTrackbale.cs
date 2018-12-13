namespace HuaweiARUnitySDK
{
    using System;
    using UnityEngine;
    using HuaweiARInternal;
    using System.Collections.Generic;
    public abstract class ARTrackable
    {
        public enum TrackingState
        {
            TRACKING = 0, PAUSED = 1, STOPPED = 2
        }

        internal IntPtr m_trackableHandle = IntPtr.Zero;
        internal NDKSession m_ndkSession;

        internal ARTrackable()
        {

        }
        internal ARTrackable(IntPtr trackableHandle,NDKSession session)
        {
            m_trackableHandle = trackableHandle;
            m_ndkSession = session;
        }
        ~ARTrackable()
        {
            m_ndkSession.TrackableAdapter.Release(m_trackableHandle);
        }

        public virtual TrackingState GetTrackingState()
        {
            return m_ndkSession.TrackableAdapter.GetTrackingState(m_trackableHandle);
        }
        public virtual ARAnchor CreateAnchor(Pose pose)
        {
            IntPtr anchorHandle = IntPtr.Zero;

            if(!m_ndkSession.TrackableAdapter.AcquireNewAnchor(m_trackableHandle,pose,out anchorHandle))
            {
                ARDebug.LogError("failed to create anchor on trackbale");
                return null;
            }
            return m_ndkSession.AnchorManager.ARAnchorFactory(anchorHandle, true);
        }

        public virtual void GetAllAnchors(List<ARAnchor> anchors)
        {
            if (anchors == null)
            {
                throw new ArgumentNullException();
            }
            m_ndkSession.TrackableAdapter.GetAnchors(m_trackableHandle, anchors);
        }


        public override bool Equals(object obj)
        {
            if (obj != null && obj is ARTrackable)
            {
                ARTrackable other = (ARTrackable)obj;
                if (other.m_trackableHandle == m_trackableHandle)
                {
                    return true;
                }
            }
            return false;
        }

        public override int GetHashCode()
        {
            return m_trackableHandle.ToInt32();
        }
    }
}
