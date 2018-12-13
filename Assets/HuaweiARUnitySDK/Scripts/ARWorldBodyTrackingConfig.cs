namespace HuaweiARUnitySDK
{
    using HuaweiARInternal;
    using System;
    using UnityEngine;

    [CreateAssetMenu(fileName = "HuaweiARConfig", menuName = "HuaweiARUnitySDK/WorldBodyTrackingConfig", order = 5)]
    public class ARWorldBodyTrackingConfig:ARConfigBase
    {
        public ARConfigPlaneFindingMode PlaneFindingMode = ARConfigPlaneFindingMode.DISABLE;
        public ARAugmentedImageDatabase AugmentedImageDatabase = null;

        internal override ARAugmentedImageDatabase GetAugImgDataBaseHandle() { return AugmentedImageDatabase; }

        internal override ARConfigPlaneFindingMode GetPlaneFindingMode() { return PlaneFindingMode; }
        internal override void SetPlaneFindingMode(ARConfigPlaneFindingMode mode)
        {
            PlaneFindingMode = mode;
        }
        internal override int GetARType() { return (int)NDKARType.BODY_AR|(int)NDKARType.WORLD_AR; }
        public override string ToString()
        {
            return string.Format("Config Type:{0}, LightingMode:{1}, UpdateMode:{2}, PlanFindingMode:{3}, PowerMode:{4} ",
                "BodyWordTracking",  LightingMode, UpdateMode, PlaneFindingMode, PowerMode);
        }
    }
}
