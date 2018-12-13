namespace HuaweiARUnitySDK
{
    using HuaweiARInternal;
    using System;
    [Obsolete]
    public class ARPlaneHitResult:ARHitResult
    {
        public ARPlane Plane
        {
            get
            {
                ARTrackable trackable = GetTrackable();
                return trackable is ARPlane ? (ARPlane)trackable : null;
            }
        }

        public bool IsHitInExtents
        {
            get
            {
                return Plane == null ? false : Plane.IsPoseInExtents(HitPose);
            }
        }

        public bool IsHitInPolygon
        {
            get
            {
                return Plane == null ? false : Plane.IsPoseInPolygon(HitPose);
            }
        }

        internal ARPlaneHitResult(IntPtr planeHitResult, NDKSession session) : base(planeHitResult, session) { }

        public bool IsHitOnFrontFace { get { return true; } }//Deprecated member
    }
}
