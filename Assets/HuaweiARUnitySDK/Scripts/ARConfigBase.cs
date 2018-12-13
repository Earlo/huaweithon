namespace HuaweiARUnitySDK
{
    using HuaweiARInternal;
    using System;
    using UnityEngine;

    public abstract class ARConfigBase: ScriptableObject
    {
        public ARConfigLightingMode LightingMode = ARConfigLightingMode.AMBIENT_INTENSITY;
        public ARConfigUpdateMode UpdateMode = ARConfigUpdateMode.BLOCKING;
        public ARConfigPowerMode PowerMode = ARConfigPowerMode.NORMAL;
        public bool EnableDepth = true;
        public bool EnableMask = false;
        internal virtual ARAugmentedImageDatabase GetAugImgDataBaseHandle() { return null; }
        internal abstract int GetARType();
        internal virtual ARConfigPlaneFindingMode GetPlaneFindingMode() { return ARConfigPlaneFindingMode.DISABLE; }
        internal virtual ARConfigCameraLensFacing GetCameraLensFacing() { return ARConfigCameraLensFacing.REAR; }
        internal virtual ARConfigLightingMode GetLightingMode() { return LightingMode; }
        internal virtual ARConfigUpdateMode GetUpdateMode() { return UpdateMode; }
        internal virtual ARConfigPowerMode GetPowerMode() { return PowerMode; }
        [Obsolete]
        internal virtual ARConfigHandFindingMode GetHandFindingMode() { return ARConfigHandFindingMode.DISABLED; }

        internal virtual void SetPlaneFindingMode(ARConfigPlaneFindingMode mode) { ; }
        internal virtual void SetCameraLensFacing(ARConfigCameraLensFacing lensFacing) { ; }
        internal virtual void SetLightingMode(ARConfigLightingMode lightingMode) { LightingMode=lightingMode; }
        internal virtual void SetUpdateMode(ARConfigUpdateMode updateMode) { UpdateMode = updateMode; }
        internal virtual void SetPowerMode(ARConfigPowerMode powerMode) { PowerMode = powerMode; }
        [Obsolete]
        internal virtual void SetHandFindingMode(ARConfigHandFindingMode mode) { ; }

        internal const int EnableItem_None = 0;
        internal const int EnableItem_Depth = 1 << 0;
        internal const int EnableItem_Mask = 1 << 1;
        internal virtual ulong GetConfigEnableItem()
        {
            ulong ret = EnableItem_None;
            ret = EnableDepth ? ret | EnableItem_Depth : ret;
            ret = EnableMask ? ret | EnableItem_Mask : ret;
            return ret;
        }
    }
}
