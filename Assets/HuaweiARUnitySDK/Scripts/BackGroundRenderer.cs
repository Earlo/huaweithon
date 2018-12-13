namespace HuaweiARUnitySDK
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;
    using UnityEngine.XR;
    using HuaweiARInternal;
    public class BackGroundRenderer : MonoBehaviour
    {
        private Camera m_camera;
        private ARBackgroundRenderer m_backgroundRenderer;
        private static float[] QUAD_TEXCOORDS = { 0f, 1f, 0f, 0f, 1f, 1f, 1f, 0f };
        private float[] transformedUVCoords = QUAD_TEXCOORDS;
        public Material BackGroundMaterial;

        private void Start()
        {
            m_camera = GetComponent<Camera>();
        }

        public void Update()
        {
            if (BackGroundMaterial == null)
            {
                return;
            }
            else if (!ARFrame.TextureIsAvailable())
            {
                return;
            }

            const string backroundTex = "_MainTex";
            const string leftTopBottom = "_UvLeftTopBottom";
            const string rightTopBottom = "_UvRightTopBottom";

            BackGroundMaterial.SetTexture(backroundTex, ARFrame.CameraTexture);

            if (ARFrame.IsDisplayGeometryChanged())
            {
                transformedUVCoords = ARFrame.GetTransformDisplayUvCoords(QUAD_TEXCOORDS);
            }

            BackGroundMaterial.SetVector(leftTopBottom, new Vector4(transformedUVCoords[0], transformedUVCoords[1],
                transformedUVCoords[2], transformedUVCoords[3]));
            BackGroundMaterial.SetVector(rightTopBottom, new Vector4(transformedUVCoords[4], transformedUVCoords[5],
                transformedUVCoords[6], transformedUVCoords[7]));
            Pose p = ARFrame.GetPose();
            m_camera.transform.position = p.position;
            m_camera.transform.rotation = p.rotation;
            m_camera.projectionMatrix = ARSession.GetProjectionMatrix(m_camera.nearClipPlane, m_camera.farClipPlane);

            if (m_backgroundRenderer == null)
            {
                m_backgroundRenderer = new ARBackgroundRenderer();
                m_backgroundRenderer.backgroundMaterial = BackGroundMaterial;
                m_backgroundRenderer.camera = m_camera;
                m_backgroundRenderer.mode = ARRenderMode.MaterialAsBackground;
            }
        }
    }
}