namespace HuaweiARUnitySDK
{
    using HuaweiARInternal;
    using System;
    using UnityEngine;
    using System.Collections.Generic;

    public class ARHand : ARTrackable
    {

        internal ARHand(IntPtr trackableHandle, NDKSession session) : base(trackableHandle, session)
        {

        }

        public ARCoordinateSystemType GetGestureCoordinateSystemType()
        {
            return m_ndkSession.HandAdapter.GetGestureCoordinateSystemType(m_trackableHandle);
        }

        public HandType GetHandType()
        {
            return m_ndkSession.HandAdapter.GetHandType(m_trackableHandle);
        }

        public int GetGestureType()
        {
            return m_ndkSession.HandAdapter.GetGustureType(m_trackableHandle);
        }

        public Vector3[] GetHandBox()
        {
            return m_ndkSession.HandAdapter.GetHandBox(m_trackableHandle);
        }

        public Vector3 GetGestureCenter()
        {
            return m_ndkSession.HandAdapter.GetGestureCenter(m_trackableHandle);
        }

        public int[] GetGestureAction()
        {
            return m_ndkSession.HandAdapter.GetGestureAction(m_trackableHandle);
        }

        public Vector4 GetGestureOrientation()
        {
            return m_ndkSession.HandAdapter.GetGestureOrientation(m_trackableHandle);
        }

        public ARCoordinateSystemType GetSkeletonCoordinateSystemType()
        {
            return m_ndkSession.HandAdapter.GetSkeletonCoordinateSystemType(m_trackableHandle);
        }

        public int GetHandSkeletonCount()
        {
            return m_ndkSession.HandAdapter.GetHandSkeletonCount(m_trackableHandle);
        }


        public void GetSkeletons(Dictionary<SkeletonPointName, SkeletonPointEntry> outSkeleton)
        {
            if (null == outSkeleton)
            {
                throw new ArgumentNullException();
            }
            outSkeleton.Clear();

            int[] skeletonType = m_ndkSession.HandAdapter.GetHandSkeletonType(m_trackableHandle);

            Vector3[] points = m_ndkSession.HandAdapter.GetHandSkeletonData(m_trackableHandle);
            for (int i = 0; i < skeletonType.Length; i++)
            {
                if (!ValueLegalityChecker.CheckInt("GetSkeletons", skeletonType[i], 0,
                    (int)SkeletonPointName.SKELETON_LENGTH - 1))
                {
                    continue;
                }
                outSkeleton.Add((SkeletonPointName)skeletonType[i], new SkeletonPointEntry(points[i]));
            }
        }

        public void GetSkeletonConnection(List<KeyValuePair<SkeletonPointName, SkeletonPointName>> outConnections)
        {
            if (null == outConnections)
            {
                throw new ArgumentNullException();
            }
            outConnections.Clear();
            Vector2Int[] connections = m_ndkSession.HandAdapter.GetSkeletonConnection(m_trackableHandle);

            for (int i = 0; i < connections.Length; i++)
            {
                if (!ValueLegalityChecker.CheckInt("GetSkeletonConnection", connections[i].x, 0,
                    (int)SkeletonPointName.SKELETON_LENGTH - 1) ||
                    !ValueLegalityChecker.CheckInt("GetSkeletonConnection", connections[i].y, 0,
                    (int)SkeletonPointName.SKELETON_LENGTH - 1))
                {
                    continue;
                }
                outConnections.Add(new KeyValuePair<SkeletonPointName, SkeletonPointName>(
                    (SkeletonPointName)connections[i].x, (SkeletonPointName)connections[i].y));
            }
        }

        public struct SkeletonPointEntry
        {
            internal SkeletonPointEntry(Vector3 vector)
            {
                Coordinate = vector;
            }
            public Vector3 Coordinate { get; private set; }
        }


        public enum HandType
        {
            UNKNOWN = -1,
            RIGHT = 0,
            LEFT = 1,
        }

        public enum SkeletonPointName
        {
            Root = 0,
            Pinky_1 = 1,
            Pinky_2 = 2,
            Pinky_3 = 3,
            Pinky_4 = 4,
            Ring_1 = 5,
            Ring_2 = 6,
            Ring_3 = 7,
            Ring_4 = 8,
            Middle_1 = 9,
            Middle_2 = 10,
            Middle_3 = 11,
            Middle_4 = 12,
            Index_1 = 13,
            Index_2 = 14,
            Index_3 = 15,
            Index_4 = 16,
            Thumb_1 = 17,
            Thumb_2 = 18,
            Thumb_3 = 19,
            Thumb_4 = 20,
            SKELETON_LENGTH = 21
        };
    }
}
