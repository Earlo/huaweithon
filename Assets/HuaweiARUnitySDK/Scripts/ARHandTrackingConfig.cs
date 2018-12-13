namespace HuaweiARUnitySDK
{
    using HuaweiARInternal;
    using System;
    using UnityEngine;

    [CreateAssetMenu(fileName = "HuaweiARConfig", menuName = "HuaweiARUnitySDK/HandTrackingConfig", order = 4)]
    public class ARHandTrackingConfig : ARConfigBase
    {
        private NDKARType arType = NDKARType.HAND_AR;
        public ARConfigCameraLensFacing CameraLensFacing = ARConfigCameraLensFacing.REAR;

        [Obsolete]
        public ARConfigHandFindingMode HandFindingMode = ARConfigHandFindingMode.ENABLE_2D;

        internal override ARConfigCameraLensFacing GetCameraLensFacing() { return CameraLensFacing; }
        internal override void SetCameraLensFacing(ARConfigCameraLensFacing lensFacing)
        {
            CameraLensFacing = lensFacing;
        }
        internal override int GetARType(){return (int)arType;}
        [Obsolete]
        internal override ARConfigHandFindingMode GetHandFindingMode()
        {
            return HandFindingMode;
        }
        [Obsolete]
        internal override void SetHandFindingMode(ARConfigHandFindingMode findingMode)
        {
            HandFindingMode = findingMode;
        }

        public override string ToString()
        {
            return string.Format("Config Type:{0}, CameraLensFacing:{1}, LightingMode:{2}, UpdateMode:{3}, PowerMode:{4} ",
                arType, CameraLensFacing, LightingMode, UpdateMode, PowerMode);
        }
    }
}
