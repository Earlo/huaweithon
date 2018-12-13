
namespace HuaweiARUnitySDK
{
    using HuaweiARInternal;
    using System;
    [Obsolete]
    public class ARPointCloudHitResult:ARHitResult
    {
        public ARPointCloud PointCloud { get; private set; }
        internal ARPointCloudHitResult(IntPtr hitResultHandle,NDKSession session,ARPointCloud pointCloud)
            : base(hitResultHandle, session)
        {
            PointCloud = pointCloud;
        }

    }
}
