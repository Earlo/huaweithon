namespace HuaweiARUnitySDK 
{
    using System;
    using System.Collections.Generic;
    using HuaweiARInternal;
    using UnityEngine;

    public class AndroidPermissionsRequest : AndroidJavaProxy
    {
        private static AndroidPermissionsRequest m_instance;
        private static AndroidJavaObject m_permissionRequestInJava;
        private static AsyncTask<AndroidPermissionsRequestResult> m_currentRequest = null;
        private static Action<AndroidPermissionsRequestResult> m_onPermissionsRequestFinished;

        public static AndroidPermissionsRequest Instance
        {
            get
            {
                if (m_instance == null)
                {
                    m_instance = new AndroidPermissionsRequest();
                }
                return m_instance;
            }
        }

        public static AndroidJavaObject UnityActivity
        {
            get
            {
                AndroidJavaClass unityPlayer = new AndroidJavaClass("com.unity3d.player.UnityPlayer");
                AndroidJavaObject m_unityMainActivity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity");
                return m_unityMainActivity;
            }
        }

        private static AndroidJavaObject AndroidPermissionsService
        {
            get
            {
                if (m_permissionRequestInJava == null)
                {
                    m_permissionRequestInJava = new AndroidJavaObject("com.huawei.hiar.UnityAndroidPermissions");
                }
                return m_permissionRequestInJava;
            }
        }

        public static bool IsPermissionGranted(string permissionName)
        {
            return AndroidPermissionsService.Call<bool>("IsPermissionGranted", UnityActivity, permissionName);
        }

        //support for multiple permission request
        public static AsyncTask<AndroidPermissionsRequestResult> RequestPermission(string[] permissionNames)
        {
            if (m_currentRequest != null)
            {
                ARDebug.LogError("Do not make simultaneous permission requests.");
                return null;
            }

            AndroidPermissionsService.Call("RequestPermissionAsync", UnityActivity, permissionNames, Instance);
            m_currentRequest = new AsyncTask<AndroidPermissionsRequestResult>(out m_onPermissionsRequestFinished);

            return m_currentRequest;
        }


        public AndroidPermissionsRequest() : base("com.huawei.hiar.UnityAndroidPermissions$IPermissionRequestResult") { }

        public virtual void OnRequestPermissionsResult(string result)
        {
            var permissionResults = _parseString(result);
            if (m_onPermissionsRequestFinished == null)
            {
                Debug.LogError("AndroidPermissionsRequest error");
                return;
            }
            var onRequestFinished = m_onPermissionsRequestFinished;
            m_currentRequest = null;
            m_onPermissionsRequestFinished = null;
            onRequestFinished(new AndroidPermissionsRequestResult(permissionResults));
        }


        private AndroidPermissionsRequestResult.PermissionResult[] _parseString(string result)
        {
            string newJson = result.Substring(1, result.Length - 2);
            char[] seprator = { ',' };
            string[] results = newJson.Split(seprator);
            var permissionResultList =
                new List<AndroidPermissionsRequestResult.PermissionResult>();
            char[] itemSep = { ':' };
            foreach (var value in results)
            {
                string[] item = value.Substring(1, value.Length - 2).Split(itemSep);
                var pr = new AndroidPermissionsRequestResult.PermissionResult();
                pr.permissionName = item[0];
                pr.granted = int.Parse(item[1]);
                permissionResultList.Add(pr);
            }
            return permissionResultList.ToArray();
        }
    }
}
