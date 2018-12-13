namespace HuaweiARUnitySDK
{
    using UnityEngine;
    using System;
    using HuaweiARInternal;
    public class ARFaceGeometry
    {
        private IntPtr m_faceGeometryHandle;
        private NDKSession m_session;

        internal ARFaceGeometry(IntPtr handle, NDKSession session)
        {
            m_faceGeometryHandle = handle;
            m_session = session;
        }
        ~ARFaceGeometry()
        {
            m_session.FaceGeometryAdapter.Release(m_faceGeometryHandle);
        }
        public Vector3[] Vertices
        {
            get
            {
                return m_session.FaceGeometryAdapter.GetVertices(m_faceGeometryHandle);
            }
        }
        public Vector2[] TextureCoordinates
        {
            get
            {
                return m_session.FaceGeometryAdapter.GetTexCoord(m_faceGeometryHandle);
            }
        }
        public int TriangleCount
        {
            get
            {
                return m_session.FaceGeometryAdapter.GetTriangleCount(m_faceGeometryHandle);
            }
        }
        public int[] TriangleIndices
        {
            get
            {
                return m_session.FaceGeometryAdapter.GetTriangleIndex(m_faceGeometryHandle);
            }
        }

        public Label[] TriangleLabel
        {
            get
            {
                return m_session.FaceGeometryAdapter.GetTriangleLabels(m_faceGeometryHandle);
            }
        }
        public enum Label
        {
            Label_Non_Face = -1,
            Label_Face_Other = 0,
            Label_Lower_Lip = 1,
            Label_Upper_Lip = 2,
            Label_Left_Eye = 3,
            Label_Right_Eye = 4,
            Label_Left_Brow = 5,
            Label_Right_Brow = 6,
            Label_Brow_Center = 7,
            Label_Nose = 8,
            LABELS_LENGTH=9
        }
    }
}
