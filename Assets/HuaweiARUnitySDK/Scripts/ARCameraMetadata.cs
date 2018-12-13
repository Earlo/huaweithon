namespace HuaweiARUnitySDK
{
    using HuaweiARInternal;
    using System;
    using UnityEngine;
    using System.Collections.Generic;

    public class ARCameraMetadata
    {
        private IntPtr m_metadataPtr;
        private NDKSession m_ndkSession;

        internal ARCameraMetadata(IntPtr metadataPtr,NDKSession session)
        {
            m_metadataPtr = metadataPtr;
            m_ndkSession = session;
        }

        public List<ARCameraMetadataTag> GetAllCameraMetadataTags()
        {
            List<ARCameraMetadataTag> metadataTags = new List<ARCameraMetadataTag>();
            m_ndkSession.CameraMetadataAdapter.GetAllCameraMetadataTags(m_metadataPtr, metadataTags);
            return metadataTags;
        }

        public List<ARCameraMetadataValue> GetValue(ARCameraMetadataTag cameraMetadataTag)
        {
            List<ARCameraMetadataValue> metadataValues = new List<ARCameraMetadataValue>();
            m_ndkSession.CameraMetadataAdapter.GetValues(m_metadataPtr, cameraMetadataTag, metadataValues);
            return metadataValues;
        }

        ~ARCameraMetadata()
        {
            m_ndkSession.CameraMetadataAdapter.Release(m_metadataPtr);
        }
    }
}
