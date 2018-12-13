namespace HuaweiARUnitySDK
{
    using HuaweiARInternal;
    using System;
    using UnityEngine;

    [CreateAssetMenu(fileName = "HuaweiARConfig", menuName = "HuaweiARUnitySDK/FaceTrackingConfig", order = 3)]
    public class ARFaceTrackingConfig : ARConfigBase
    {
        private NDKARType arType = NDKARType.FACE_AR;
        private ARConfigCameraLensFacing CameraLensFacing = ARConfigCameraLensFacing.FRONT;
        
        internal override ARConfigCameraLensFacing GetCameraLensFacing() { return CameraLensFacing; }
        internal override void SetCameraLensFacing(ARConfigCameraLensFacing lensFacing)
        {
            CameraLensFacing = lensFacing;
        }
        internal override int GetARType() { return (int)arType; }
        public override string ToString()
        {
            return string.Format("Config Type:{0}, CameraLensFacing:{1}, LightingMode:{2} ,UpdateMode:{3}, PowerMode:{4} ",
                arType, CameraLensFacing, LightingMode, UpdateMode, PowerMode);
        }
    }
}
