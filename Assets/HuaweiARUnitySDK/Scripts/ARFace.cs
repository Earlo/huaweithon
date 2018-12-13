namespace HuaweiARUnitySDK
{
    using HuaweiARInternal;
    using System;
    using System.Collections.Generic;
    using UnityEngine;

    public class ARFace : ARTrackable
    {
        internal ARFace(IntPtr faceHandle, NDKSession session) : base(faceHandle, session)
        {
        }

        public Pose GetPose()
        {
            return m_ndkSession.FaceAdapter.GetPose(m_trackableHandle);
        }

        public ARFaceGeometry GetFraceGeometry()
        {
            IntPtr faceGeometryHandle = m_ndkSession.FaceAdapter.AcquireGeometry(m_trackableHandle);
            return new ARFaceGeometry(faceGeometryHandle,m_ndkSession);
        }

        public Dictionary<BlendShapeLocation, float> GetBlendShape()
        {
            IntPtr blendShapeHandle = m_ndkSession.FaceAdapter.AcquireBlendShape(m_trackableHandle);
            Dictionary<BlendShapeLocation, float> ret = m_ndkSession.FaceBlendShapeAdapter.GetBlendShapeData(blendShapeHandle);
            m_ndkSession.FaceBlendShapeAdapter.Release(blendShapeHandle);
            return ret;
        }

        public Dictionary<string, float> GetBlendShapeWithBlendName()
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();
            Dictionary<BlendShapeLocation, float> tmp = GetBlendShape();
            foreach(KeyValuePair<BlendShapeLocation,float> item in tmp)
            {
                ret.Add(item.Key.ToString(), item.Value);
            }
            return ret;
        }


        public enum BlendShapeLocation
        {
            Animoji_Eye_Blink_Left = 0,
            Animoji_Eye_Look_Down_Left = 1,
            Animoji_Eye_Look_In_Left = 2,
            Animoji_Eye_Look_Out_Left = 3,
            Animoji_Eye_Look_Up_Left = 4,
            Animoji_Eye_Squint_Left = 5,
            Animoji_Eye_Wide_Left = 6,
            Animoji_Eye_Blink_Right = 7,
            Animoji_Eye_Look_Down_Right = 8,
            Animoji_Eye_Look_In_Right = 9,
            Animoji_Eye_Look_Out_Right = 10,
            Animoji_Eye_Look_Up_Right = 11,
            Animoji_Eye_Squint_Right = 12,
            Animoji_Eye_Wide_Right = 13,
            Animoji_Jaw_Forward = 14,
            Animoji_Jaw_Left = 15,
            Animoji_Jaw_Right = 16,
            Animoji_Jaw_Open = 17,
            Animoji_Mouth_Funnel = 18,
            Animoji_Mouth_Pucker = 19,
            Animoji_Mouth_Left = 20,
            Animoji_Mouth_Right = 21,
            Animoji_Mouth_Smile_Left = 22,
            Animoji_Mouth_Smile_Right = 23,
            Animoji_Mouth_Frown_Left = 24,
            Animoji_Mouth_Frown_Right = 25,
            Animoji_Mouth_Dimple_Left = 26,
            Animoji_Mouth_Dimple_Right = 27,
            Animoji_Mouth_Stretch_Left = 28,
            Animoji_Mouth_Stretch_Right = 29,
            Animoji_Mouth_Roll_Lower = 30,
            Animoji_Mouth_Roll_Upper = 31,
            Animoji_Mouth_Shrug_Lower = 32,
            Animoji_Mouth_Shrug_Upper = 33,
            Animoji_Mouth_Upper_Up = 34,
            Animoji_Mouth_Lower_Down = 35,
            Animoji_Mouth_Lower_Out = 36,
            Animoji_Brow_Down_Left = 37,
            Animoji_Brow_Down_Right = 38,
            Animoji_Brow_Inner_Up = 39,
            Animoji_Brow_Outter_Up_Left = 40,
            Animoji_Brow_Outter_Up_Right = 41,
            Animoji_Cheek_Puff = 42,
            Animoji_Cheek_Squint_Left = 43,
            Animoji_Cheek_Squint_Right = 44,
            Animoji_Frown_Nose_Mouth_Up = 45,
            Animoji_Tongue_In = 46,
            Animoji_Tongue_Out_Slight = 47,
            Animoji_Tongue_Left = 48,
            Animoji_Tongue_Right = 49,
            Animoji_Tongue_Up = 50,
            Animoji_Tongue_Down = 51,
            Animoji_Tongue_Left_Up = 52,
            Animoji_Tongue_Left_Down = 53,
            Animoji_Tongue_Right_Up = 54,
            Animoji_Tongue_Right_Down = 55,
            Animoji_Left_EyeBall_Left = 56,
            Animoji_Left_EyeBall_Right = 57,
            Animoji_Left_EyeBall_Up = 58,
            Animoji_Left_EyeBall_Down = 59,
            Animoji_Right_EyeBall_Left = 60,
            Animoji_Right_EyeBall_Right = 61,
            Animoji_Right_EyeBall_Up = 62,
            Animoji_Right_EyeBall_Down = 63,
            Animoji_BLENDSHAPE_LENGTH = 64,
        }
    }
}
