namespace HuaweiARUnitySDK
{
    using System;
    using HuaweiARInternal;
    using UnityEngine;
    using System.Collections.Generic;

    public class ARSession
    {
        /// <exception cref="ARUnavailableDeviceNotCompatibleException">Thrown when device does not support AR</exception>
        public static void CreateSession()
        {
            ARSessionManager.Instance.CreateSession();
        }
        /// <exception cref="ARSessionPausedException">Thrown when session is paused</exception>
        public static void Update()
        {
            ARSessionManager.Instance.Update();
        }
        /// <exception cref="ARCameraPermissionDeniedException">Thrown when camera request is denied</exception>
        public static void Resume()
        {
            ARSessionManager.Instance.Resume();
        }

        public static void Pause()
        {
            ARSessionManager.Instance.Pause();
        }

        public static void Stop()
        {
            ARSessionManager.Instance.Stop();
        }


        public static void SetCameraTextureNameAuto()
        {
            ARSessionManager.Instance.SetCameraTextureName();
        }
        public static void SetDisplayGeometry(int width, int height)
        {
            ARSessionManager.Instance.SetDisplayGeometry(width, height);
        }

        public static ARAnchor AddAnchor(Pose pose)
        {
            ARAnchor anchor = ARSessionManager.Instance.AddAnchor(pose);
            return anchor;
        }

        /// <exception cref="ARUnSupportedConfigurationException">Thrown when config is not supported</exception>
        public static void Config(ARConfigBase config)
        {
            ARSessionManager.Instance.Config(config);
        }

        [Obsolete]
        public static bool IsSupported(ARConfigBase config)
        {
            return true;
        }

        [Obsolete]
        public static void Resume(ARConfigBase config)
        {
            Config(config);
            Resume();
        }


        [Obsolete]
        public static void RemoveAnchors(List<ARAnchor> anchors)
        {
            if (anchors == null)
            {
                throw new ArgumentNullException();
            }
            foreach(ARAnchor anchor in anchors)
            {
                anchor.Detach();
            }
        }


        [Obsolete]
        public static List<ARAnchor> GetAllAnchors()
        {
            return ARFrame.GetAnchors(ARTrackableQueryFilter.ALL);
        }

        
        public static Matrix4x4 GetProjectionMatrix(float nearClipPlane, float farClipPlane)
        {
            return ARSessionManager.Instance.GetProjectionMatrix(nearClipPlane, farClipPlane); ;
        }

        [Obsolete]
        public static List<ARPlane> GetAllPlanes()
        {
            return ARFrame.GetPlanes(ARTrackableQueryFilter.ALL); ;
        }
    }
}
