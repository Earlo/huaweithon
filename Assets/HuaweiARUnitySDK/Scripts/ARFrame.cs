namespace HuaweiARUnitySDK
{
    using HuaweiARInternal;
    using System;
    using UnityEngine;
    using System.Collections.Generic;
    public static class ARFrame
    {

        public static bool TextureIsAvailable()
        {
            return ARSessionManager.Instance.SessionStatus == ARSessionStatus.RUNNING;
        }
        public static Texture2D CameraTexture
        {
            get
            {
                return ARSessionManager.Instance.BackgroundTexture;
            }
        }

        public static float[] GetTransformDisplayUvCoords(float[] inUVCoords)
        {
            if (null == inUVCoords || inUVCoords.Length != 8)
            {
                ARDebug.LogError("wrong inUVCoords");
                throw new ArgumentException("inUVCoords is wrong");
            }
            if (ARSessionManager.Instance.SessionStatus != ARSessionStatus.RUNNING &&
                    ARSessionManager.Instance.SessionStatus != ARSessionStatus.PAUSED)
            {
                throw new ARNotYetAvailableException();
            }

            float[] outUv = ARSessionManager.Instance.m_ndkSession.FrameAdapter.TransformDisplayUvCoords(inUVCoords);
            return outUv;
        }

        public static Pose GetPose()
        {
            if (ARSessionManager.Instance.SessionStatus != ARSessionStatus.RUNNING &&
                    ARSessionManager.Instance.SessionStatus != ARSessionStatus.PAUSED)
            {
                return Pose.identity;
            }

            IntPtr cameraPtr = ARSessionManager.Instance.m_ndkSession.FrameAdapter.AcquireCameraHandle();
            Pose p = ARSessionManager.Instance.m_ndkSession.CameraAdapter.GetPose(cameraPtr);
            ARSessionManager.Instance.m_ndkSession.CameraAdapter.Release(cameraPtr);
            return p;
        }

        public static ARLightEstimate GetLightEstimate()
        {
            if (ARSessionManager.Instance.SessionStatus != ARSessionStatus.RUNNING &&
                    ARSessionManager.Instance.SessionStatus != ARSessionStatus.PAUSED)
            {
                return new ARLightEstimate(false, 1.0f);
            }
            ARLightEstimate lightEstimate = ARSessionManager.Instance.m_ndkSession.FrameAdapter.GetLightEstimate();
            return lightEstimate;
        }

        public static ARPointCloud AcquirePointCloud()
        {
            if (ARSessionManager.Instance.SessionStatus != ARSessionStatus.RUNNING &&
                    ARSessionManager.Instance.SessionStatus != ARSessionStatus.PAUSED)
            {
                throw new ARNotYetAvailableException();
            }

            IntPtr pointcloudHandle = ARSessionManager.Instance.m_ndkSession.FrameAdapter.AcquirePointCloudHandle();
            ARPointCloud pointCloud = new ARPointCloud(pointcloudHandle, ARSessionManager.Instance.m_ndkSession);
            return pointCloud;
        }
        public static long GetTimestampNs()
        {
            if (ARSessionManager.Instance.SessionStatus != ARSessionStatus.RUNNING &&
                    ARSessionManager.Instance.SessionStatus != ARSessionStatus.PAUSED)
            {
                return 0;
            }

            long timestamp = ARSessionManager.Instance.m_ndkSession.FrameAdapter.GetTimestamp();
            return timestamp;
        }

        public static ARTrackable.TrackingState GetTrackingState()
        {
            if (ARSessionManager.Instance.SessionStatus != ARSessionStatus.RUNNING &&
                ARSessionManager.Instance.SessionStatus != ARSessionStatus.PAUSED)
            {
                return ARTrackable.TrackingState.STOPPED;
            }
            IntPtr cameraPtr = ARSessionManager.Instance.m_ndkSession.FrameAdapter.AcquireCameraHandle();
            ARTrackable.TrackingState state = ARSessionManager.Instance.m_ndkSession.CameraAdapter.GetTrackingState(cameraPtr);
            ARSessionManager.Instance.m_ndkSession.CameraAdapter.Release(cameraPtr);
            return state;
        }


        public static List<ARAnchor> GetAnchors(ARTrackableQueryFilter filter)
        {
            if (ARSessionManager.Instance.SessionStatus != ARSessionStatus.RUNNING &&
                    ARSessionManager.Instance.SessionStatus != ARSessionStatus.PAUSED)
            {
                return new List<ARAnchor>();
            }

            switch (filter)
            {
                case ARTrackableQueryFilter.ALL:
                    List<ARAnchor> anchors = new List<ARAnchor>();
                    ARSessionManager.Instance.m_ndkSession.AnchorManager.GetAllAnchor(anchors);
                    return anchors;
                case ARTrackableQueryFilter.UPDATED:
                    List<ARAnchor> anchorList = new List<ARAnchor>();
                    ARSessionManager.Instance.m_ndkSession.FrameAdapter.GetUpdatedAnchors(anchorList);
                    return anchorList;
                case ARTrackableQueryFilter.NEW:
                default:
                    return new List<ARAnchor>();
            }
        }

        public static void GetTrackables<T>(List<T> trackableList, ARTrackableQueryFilter filter) where T : ARTrackable
        {
            if (trackableList == null)
            {
                throw new ArgumentException();
            }
            if (ARSessionManager.Instance.SessionStatus != ARSessionStatus.RUNNING &&
                    ARSessionManager.Instance.SessionStatus != ARSessionStatus.PAUSED)
            {
                trackableList.Clear();
                return;
            }
            ARSessionManager.Instance.m_ndkSession.TrackableManager.GetTrackables<T>(trackableList, filter);
        }

        public static List<ARHitResult> HitTest(Touch touch)
        {
            if (ARSessionManager.Instance.SessionStatus != ARSessionStatus.RUNNING &&
                    ARSessionManager.Instance.SessionStatus != ARSessionStatus.PAUSED)
            {
                return new List<ARHitResult>();
            }

            List<ARHitResult> res = HitTest(touch.position.x, touch.position.y);
            return res;
        }

        public static List<ARHitResult> HitTest(float xPx, float yPx)
        {
            if (ARSessionManager.Instance.SessionStatus != ARSessionStatus.RUNNING &&
                ARSessionManager.Instance.SessionStatus != ARSessionStatus.PAUSED)
            {
                return new List<ARHitResult>();
            }
            List<ARHitResult> results = new List<ARHitResult>();
            ARSessionManager.Instance.m_ndkSession.FrameAdapter.HitTest(xPx, Screen.height - yPx, results);
            return results;
        }
        public static bool IsDisplayGeometryChanged()
        {
            if (ARSessionManager.Instance.SessionStatus != ARSessionStatus.RUNNING &&
                ARSessionManager.Instance.SessionStatus != ARSessionStatus.PAUSED)
            {
                return false;
            }
            if (ARSessionManager.Instance.DisplayGeometrySet)
            {
                ARSessionManager.Instance.DisplayGeometrySet = false;
                return true;
            }
            bool res = ARSessionManager.Instance.m_ndkSession.FrameAdapter.GetDisplayGeometryChanged();
            return res;
        }

        public static ARCameraMetadata GetCameraMetadata()
        {
            if (ARSessionManager.Instance.SessionStatus != ARSessionStatus.RUNNING &&
                ARSessionManager.Instance.SessionStatus != ARSessionStatus.PAUSED)
            {
                throw new ARNotYetAvailableException();
            }
            IntPtr metadataPtr = ARSessionManager.Instance.m_ndkSession.FrameAdapter.AcquireImageMetadata();
            return new ARCameraMetadata(metadataPtr, ARSessionManager.Instance.m_ndkSession);
        }

        [Obsolete]
        public static Pose GetPoseInUnity()
        {
            return GetPose();
        }

        [Obsolete]
        public static List<ARPlane> GetPlanes(ARTrackableQueryFilter filter)
        {
            List<ARPlane> planeList = new List<ARPlane>();
            GetTrackables<ARPlane>(planeList, filter);
            return planeList;
        }
        [Obsolete]
        public static List<ARPlane> GetUpdatedPlanes()
        {
            return GetPlanes(ARTrackableQueryFilter.UPDATED);
        }

        [Obsolete]
        public static List<ARAnchor> GetUpdatedAnchors()
        {
            return GetAnchors(ARTrackableQueryFilter.UPDATED);
        }

        [Obsolete]
        public static Matrix4x4 GetViewMatrix()
        {
            if (ARSessionManager.Instance.SessionStatus != ARSessionStatus.RUNNING &&
                ARSessionManager.Instance.SessionStatus != ARSessionStatus.PAUSED)
            {
                return Matrix4x4.identity;
            }

            Pose p = GetPose();
            return Matrix4x4.TRS(p.position, p.rotation, Vector3.one).inverse;
        }
        [Obsolete]
        public static bool IsDisplayRotationChanged()
        {
            return IsDisplayGeometryChanged();
        }
        [Obsolete]
        public static ARPointCloud GetPointCloud()
        {
            return AcquirePointCloud();
        }
    }
}
