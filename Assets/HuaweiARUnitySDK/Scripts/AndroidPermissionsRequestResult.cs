namespace HuaweiARUnitySDK
{
    public class AndroidPermissionsRequestResult
    {

        [System.Serializable]
        public class PermissionResult
        {
            public string permissionName;
            public int granted;
        }
        private PermissionResult[] m_Results;

        public bool IsAllGranted
        {
            get
            {
                if (m_Results == null)
                {
                    return false;
                }

                for (int i = 0; i < m_Results.Length; i++)
                {
                    if (0 == m_Results[i].granted)
                    {
                        return false;
                    }
                }

                return true;
            }
        }
        public AndroidPermissionsRequestResult(PermissionResult[] permissionResults)
        {
            m_Results = permissionResults;
        }

    }
}
