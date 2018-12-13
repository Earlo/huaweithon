namespace HuaweiARUnitySDK
{
    using System;
    using HuaweiARInternal;
    using UnityEngine;
    using System.Collections.Generic;
    public class ARPlane:ARTrackable
    {
        public static class PlaneType
        {
            public enum Type
            {
                HORIZONTAL_UPWARD_FACING = 0,
                HORIZONTAL_DOWNWARD_FACING = 1,
                VERTICAL_FACING = 2,
                UNKNOWN_FACING = 3,
            }
        }
        internal ARPlane(IntPtr trackableHandle, NDKSession session) : base(trackableHandle, session)
        {
        }
        public PlaneType.Type GetPlaneType()
        {
            return m_ndkSession.PlaneAdapter.GetPlaneType(m_trackableHandle);
        }
        public ARPlane GetSubsumedBy()
        {
            return m_ndkSession.PlaneAdapter.AcquireSubsumedBy(m_trackableHandle);
        }

        public Pose GetCenterPose()
        {
            return m_ndkSession.PlaneAdapter.GetCenterPose(m_trackableHandle);
        }
        public Pose GetCenterPoseInUnity()
        {
            return GetCenterPose();
        }

        public float GetExtentX()
        {
            return m_ndkSession.PlaneAdapter.GetExtentX(m_trackableHandle);
        }
        public float GetExtentZ()
        {
            return m_ndkSession.PlaneAdapter.GetExtentZ(m_trackableHandle);
        }


        public void GetPlanePolygon(List<Vector3> polygonList)
        {
            if (polygonList == null)
            {
                throw new ArgumentNullException();
            }
            m_ndkSession.PlaneAdapter.GetPlanePolygon(m_trackableHandle, polygonList);
        }
        [Obsolete]
        public void GetPlanePolygon(ref List<Vector3> polygonList)
        {
            GetPlanePolygon(polygonList);
        }

        public void GetPlanePolygon(List<Vector2> polygonList)
        {
            if (polygonList == null)
            {
                throw new ArgumentNullException();
            }
            polygonList.Clear();
            List<Vector3> polygon3D = new List<Vector3>();
            GetPlanePolygon(polygon3D);
            foreach(Vector3 point in polygon3D)
            {
                polygonList.Add(new Vector2(point.x, point.z));
            }
        }
        public void GetPlanePolygon(ref List<Vector2> polygonList)
        {
            GetPlanePolygon(polygonList);
        }

        public bool IsPoseInExtents(Pose pose)
        {
            return m_ndkSession.PlaneAdapter.IsPoseInExtents(m_trackableHandle, pose);
        }
        public bool IsPoseInPolygon(Pose pose)
        {
            return m_ndkSession.PlaneAdapter.IsPoseInPolygon(m_trackableHandle,pose);
        }
    }
}
