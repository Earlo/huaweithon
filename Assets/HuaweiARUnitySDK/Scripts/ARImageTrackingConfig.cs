namespace HuaweiARUnitySDK
{
    using HuaweiARInternal;
    using System;
    using UnityEngine;
    [CreateAssetMenu(fileName = "HuaweiARConfig", menuName = "HuaweiARUnitySDK/ImageTrackingConfig", order = 1)]
    public class ARImageTrackingConfig : ARConfigBase
    {
        private NDKARType arType = NDKARType.IMAGE_AR;

        public ARAugmentedImageDatabase AugmentedImageDatabase = null;

        internal override ARAugmentedImageDatabase GetAugImgDataBaseHandle() { return AugmentedImageDatabase; }
        internal override int GetARType() { return (int)arType; }
        public override string ToString()
        {
            return string.Format("Config Type:{0}, LightingMode:{1}", arType, LightingMode);
        }

    }
}
