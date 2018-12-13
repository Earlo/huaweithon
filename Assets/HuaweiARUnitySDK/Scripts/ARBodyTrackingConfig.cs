namespace HuaweiARUnitySDK
{
    using HuaweiARInternal;
    using System;
    using UnityEngine;
    [CreateAssetMenu(fileName = "HuaweiARConfig", menuName = "HuaweiARUnitySDK/BodyTrackingConfig", order = 2)]
    public class ARBodyTrackingConfig: ARConfigBase
    {
        private NDKARType arType = NDKARType.BODY_AR;
        public ARConfigCameraLensFacing CameraLensFacing = ARConfigCameraLensFacing.REAR;

        internal override ARConfigCameraLensFacing GetCameraLensFacing() { return CameraLensFacing; }
        internal override int GetARType() { return (int)arType; }

        internal override void SetCameraLensFacing(ARConfigCameraLensFacing lensFacing)
        {
            CameraLensFacing = lensFacing;
        }

        public override string ToString()
        {
            return string.Format("Config Type:{0}, CameraLensFacing:{1}, LightingMode:{2}, UpdateMode:{3}, PowerMode:{4} ",
                arType,CameraLensFacing,LightingMode,UpdateMode,PowerMode);
        }
    }
}
