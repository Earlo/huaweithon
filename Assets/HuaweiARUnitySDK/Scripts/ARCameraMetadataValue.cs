//-----------------------------------------------------------------------
// <copyright file="CameraMetadataValue.cs" company="Google">
//
// Copyright 2017 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// </copyright>
//-----------------------------------------------------------------------
namespace HuaweiARUnitySDK
{
    using System;
    using System.Runtime.InteropServices;
    using HuaweiARInternal;

    [StructLayout(LayoutKind.Explicit)]
    public struct ARCameraMetadataValue
    {
        [FieldOffset(0)]
        private NdkCameraMetadataType m_Type;
        [FieldOffset(4)]
        private sbyte m_ByteValue;
        [FieldOffset(4)]
        private int m_IntValue;
        [FieldOffset(4)]
        private long m_LongValue;
        [FieldOffset(4)]
        private float m_FloatValue;
        [FieldOffset(4)]
        private double m_DoubleValue;
        [FieldOffset(4)]
        private ARCameraMetadataRational m_RationalValue;

        
        public ARCameraMetadataValue(sbyte byteValue)
        {
            m_IntValue = 0;
            m_LongValue = 0;
            m_FloatValue = 0;
            m_DoubleValue = 0;
            m_RationalValue = new ARCameraMetadataRational();

            m_Type = NdkCameraMetadataType.Byte;
            m_ByteValue = byteValue;
        }

        public ARCameraMetadataValue(int intValue)
        {
            m_ByteValue = 0;
            m_LongValue = 0;
            m_FloatValue = 0;
            m_DoubleValue = 0;
            m_RationalValue = new ARCameraMetadataRational();

            m_Type = NdkCameraMetadataType.Int32;
            m_IntValue = intValue;
        }


        public ARCameraMetadataValue(long longValue)
        {
            m_ByteValue = 0;
            m_IntValue = 0;
            m_FloatValue = 0;
            m_DoubleValue = 0;
            m_RationalValue = new ARCameraMetadataRational();

            m_Type = NdkCameraMetadataType.Int64;
            m_LongValue = longValue;
        }

        public ARCameraMetadataValue(float floatValue)
        {
            m_ByteValue = 0;
            m_IntValue = 0;
            m_LongValue = 0;
            m_DoubleValue = 0;
            m_RationalValue = new ARCameraMetadataRational();

            m_Type = NdkCameraMetadataType.Float;
            m_FloatValue = floatValue;
        }


        public ARCameraMetadataValue(double doubleValue)
        {
            m_ByteValue = 0;
            m_IntValue = 0;
            m_LongValue = 0;
            m_FloatValue = 0;
            m_RationalValue = new ARCameraMetadataRational();

            m_Type = NdkCameraMetadataType.Double;
            m_DoubleValue = doubleValue;
        }

        public ARCameraMetadataValue(ARCameraMetadataRational rationalValue)
        {
            m_ByteValue = 0;
            m_IntValue = 0;
            m_LongValue = 0;
            m_FloatValue = 0;
            m_DoubleValue = 0;

            m_Type = NdkCameraMetadataType.Rational;
            m_RationalValue = rationalValue;
        }


        public Type ValueType
        {
            get
            {
                switch (m_Type)
                {
                    case NdkCameraMetadataType.Byte:
                        return typeof(Byte);
                    case NdkCameraMetadataType.Int32:
                        return typeof(int);
                    case NdkCameraMetadataType.Float:
                        return typeof(float);
                    case NdkCameraMetadataType.Int64:
                        return typeof(long);
                    case NdkCameraMetadataType.Double:
                        return typeof(double);
                    case NdkCameraMetadataType.Rational:
                        return typeof(ARCameraMetadataRational);
                    default:
                        return null;
                }
            }
        }


        public sbyte AsByte()
        {
            if (m_Type != NdkCameraMetadataType.Byte)
            {
                LogError(NdkCameraMetadataType.Byte);
            }

            return m_ByteValue;
        }


        public int AsInt()
        {
            if (m_Type != NdkCameraMetadataType.Int32)
            {
                LogError(NdkCameraMetadataType.Int32);
            }

            return m_IntValue;
        }


        public float AsFloat()
        {
            if (m_Type != NdkCameraMetadataType.Float)
            {
                LogError(NdkCameraMetadataType.Float);
            }

            return m_FloatValue;
        }


        public long AsLong()
        {
            if (m_Type != NdkCameraMetadataType.Int64)
            {
                LogError(NdkCameraMetadataType.Int64);
            }

            return m_LongValue;
        }


        public double AsDouble()
        {
            if (m_Type != NdkCameraMetadataType.Double)
            {
                LogError(NdkCameraMetadataType.Double);
            }

            return m_DoubleValue;
        }


        public ARCameraMetadataRational AsRational()
        {
            if (m_Type != NdkCameraMetadataType.Rational)
            {
                LogError(NdkCameraMetadataType.Rational);
            }

            return m_RationalValue;
        }

        private void LogError(NdkCameraMetadataType requestedType)
        {
            ARDebug.LogError("Error getting value from ARCameraMetadataType due to type mismatch. " +
                    "requested type = {0}, internal type = {1}\n" , requestedType, m_Type);
        }
    }


    [StructLayout(LayoutKind.Sequential)]
    public struct ARCameraMetadataRational
    {

        public int Numerator;

        public int Denominator;
    }
}
