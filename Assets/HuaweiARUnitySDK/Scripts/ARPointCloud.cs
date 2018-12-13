namespace HuaweiARUnitySDK
{
    using System;
    using HuaweiARInternal;
    using System.Collections.Generic;
    using UnityEngine;

    public class ARPointCloud
    {
        private IntPtr m_pointCloudHandle;
        private NDKSession m_ndkSession;

        internal ARPointCloud(IntPtr pointcloudHandle, NDKSession session)
        {
            m_ndkSession = session;
            m_pointCloudHandle = pointcloudHandle;
        }

        public void GetPoints( List<Vector3> pointList)
        {
            if(null== pointList)
            {
                throw new ArgumentNullException();
            }
            if(IntPtr.Zero == m_pointCloudHandle)
            {
                throw new ARDeadlineExceededException();
            }
            pointList.Clear();
            m_ndkSession.PointCloudAdapter.CopyPoints(m_pointCloudHandle, pointList);
        }

        public void GetPoints(ref List<Vector3> pointList)
        {
            GetPoints(pointList);
        }

        public long GetTimestampNs()
        {
            if (IntPtr.Zero == m_pointCloudHandle)
            {
                throw new ARDeadlineExceededException();
            }
            return m_ndkSession.PointCloudAdapter.GetTimestamp(m_pointCloudHandle);
        }

        public void Release()
        {
            m_ndkSession.PointCloudAdapter.Release(m_pointCloudHandle);
            m_pointCloudHandle = IntPtr.Zero;
        }

        ~ARPointCloud()
        {
            if (m_pointCloudHandle != IntPtr.Zero)
            {
                m_ndkSession.PointCloudAdapter.Release(m_pointCloudHandle);
            }
        }
    }
}
