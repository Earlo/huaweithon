namespace HuaweiARUnitySDK
{
    using HuaweiARInternal;
    using System;
    using UnityEngine;
    [CreateAssetMenu(fileName = "HuaweiARConfig", menuName = "HuaweiARUnitySDK/WorldTrackingConfig", order = 1)]
    public class ARWorldTrackingConfig : ARConfigBase
    {
        private NDKARType arType = NDKARType.WORLD_AR;

        public ARConfigPlaneFindingMode PlaneFindingMode =ARConfigPlaneFindingMode.ENABLE;
        public ARAugmentedImageDatabase AugmentedImageDatabase = null;

        internal override ARAugmentedImageDatabase GetAugImgDataBaseHandle() { return AugmentedImageDatabase; }
        internal override ARConfigPlaneFindingMode GetPlaneFindingMode() { return PlaneFindingMode; }
        internal override void SetPlaneFindingMode(ARConfigPlaneFindingMode mode)
        {
            PlaneFindingMode = mode;
        }
        internal override int GetARType() { return (int)arType; }
        public override string ToString()
        {
            return string.Format("Config Type:{0}, PlaneFindingMode:{1}, LightingMode:{2}, UpdateMode:{3}, PowerMode:{4} ",
                arType, PlaneFindingMode, LightingMode, UpdateMode, PowerMode);
        }

    }
}
