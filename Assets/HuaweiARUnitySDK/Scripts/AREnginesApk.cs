namespace HuaweiARUnitySDK
{
    using HuaweiARInternal;
    public class AREnginesApk
    {
        private HuaweiArApkAdapter m_huaweiArApkAdapter;
        private static AREnginesApk m_huaweiArApk;

        private AREnginesApk()
        {
            m_huaweiArApkAdapter = new HuaweiArApkAdapter();
        }
        public static AREnginesApk Instance
        {
            get
            {
                if (m_huaweiArApk == null) {
                    m_huaweiArApk = new AREnginesApk();
                }
                return m_huaweiArApk;
            }
        }

        public ARAvailability CheckAvailability()
        {
            return m_huaweiArApkAdapter.CheckAvailability();
        }
        public ARInstallStatus RequestInstall(bool userRequestedInstall)
        {
            return m_huaweiArApkAdapter.RequestInstall(userRequestedInstall);
        }
    }
}
