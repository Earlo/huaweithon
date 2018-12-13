namespace HuaweiARUnitySDK
{
    using System;
    using HuaweiARInternal;
    using UnityEngine;
    using System.Collections.Generic;

    public class ARBody:ARTrackable
    {

        internal ARBody(IntPtr trackableHandle, NDKSession session) : base(trackableHandle, session)
        {
            
        }

        public int GetSkeletonPointCount()
        {
            return m_ndkSession.BodyAdapter.GetSkeletonPointCount(m_trackableHandle);
        }

        public void GetSkeletons(Dictionary<SkeletonPointName, SkeletonPointEntry> outDic)
        {
            if (null == outDic)
            {
                throw new ArgumentNullException();
            }
            outDic.Clear();

            bool[] is2DValid = m_ndkSession.BodyAdapter.GetSkeletonPointIsExist_2D(m_trackableHandle);
            Vector3[] coord2D = m_ndkSession.BodyAdapter.GetSkeletonPoint2D(m_trackableHandle);
            bool[] is3DValid = m_ndkSession.BodyAdapter.GetSkeletonPointIsExist_3D(m_trackableHandle);
            Vector3[] coord3D = m_ndkSession.BodyAdapter.GetSkeletonPoint3D(m_trackableHandle);
            int[] skeletonType = m_ndkSession.BodyAdapter.GetSkeletonType(m_trackableHandle);

            int sCnt = GetSkeletonPointCount();
            for(int i = 0; i < sCnt; i++)
            {
                SkeletonPointEntry spe = new SkeletonPointEntry(is2DValid[i],coord2D[i],
                    is3DValid[i],coord3D[i]);
                if(!ValueLegalityChecker.CheckInt("GetSkeletons", skeletonType[i],
                    0, (int)SkeletonPointName.SKELETON_LENGTH-1)){
                    continue;
                }
                outDic.Add((SkeletonPointName)skeletonType[i], spe);
            }
        }

        public void GetSkeletonConnection(List<KeyValuePair<SkeletonPointName, SkeletonPointName>> outConnections)
        {
            if (null == outConnections)
            {
                throw new ArgumentNullException();
            }
            outConnections.Clear();

            Vector2Int[] connections = m_ndkSession.BodyAdapter.GetSkeletonConnection(m_trackableHandle);
            for(int i=0;i<connections.Length;i++)
            {
                if (!ValueLegalityChecker.CheckInt("GetSkeletons", connections[i].x,
                    0, (int)SkeletonPointName.SKELETON_LENGTH - 1)||
                    !ValueLegalityChecker.CheckInt("GetSkeletons", connections[i].y,
                    0, (int)SkeletonPointName.SKELETON_LENGTH - 1))
                {
                    continue;
                }
                outConnections.Add(new KeyValuePair<SkeletonPointName, SkeletonPointName>((SkeletonPointName)connections[i].x,
                    (SkeletonPointName)connections[i].y));
            }
        }

        public int GetBodyAction()
        {
            return m_ndkSession.BodyAdapter.GetBodyAction(m_trackableHandle);
        }

        public ARCoordinateSystemType GetCoordinateSystemType()
        {
            return m_ndkSession.BodyAdapter.GetCoordinateSystemType(m_trackableHandle);
        }

        public enum SkeletonPointName
        {
            Head_Top =0,
            Neck = 1,
            Right_Shoulder =2,
            Right_Elbow =3,
            Right_Wrist = 4,
            Left_Shoulder =5,
            Left_Elbow = 6,
            Left_Wrist = 7,
            Right_Hip =8,
            Right_Knee = 9,
            Right_Ankle = 10,
            Left_Hip =11,
            Left_Knee = 12,
            Left_Ankle = 13,
            Body_Center = 14,
            SKELETON_LENGTH = 15,
        }

        public struct SkeletonPointEntry
        {
            internal SkeletonPointEntry(bool valid2d,Vector2 coord2d,bool valid3d,Vector3 coord3d )
            {
                Is2DValid = valid2d;
                Coordinate2D = coord2d;
                Is3DValid = valid3d;
                Coordinate3D = coord3d;
            }
            public bool Is2DValid { get; private set; }
            public Vector3 Coordinate2D { get; private set; }
            public bool Is3DValid { get; private set; }
            public Vector3 Coordinate3D { get; private set; }
        }
    }
}
