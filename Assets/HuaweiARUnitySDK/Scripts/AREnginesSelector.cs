namespace HuaweiARUnitySDK
{
    using HuaweiARInternal;

    public class AREnginesSelector
    {

        private AREnginesSelectorAdapter m_adapter;

        private static AREnginesSelector s_executorSelector;
        private AREnginesSelector()
        {
            m_adapter = new AREnginesSelectorAdapter();
        }

        public static AREnginesSelector Instance
        {
            get
            {
                if (s_executorSelector == null)
                {
                    s_executorSelector = new AREnginesSelector();
                }
                return s_executorSelector;
            }
        }

        public AREnginesAvaliblity CheckDeviceExecuteAbility()
        {
            return m_adapter.CheckDeviceExecuteAbility();
        }

        public AREnginesType SetAREngine(AREnginesType executor)
        {
            return m_adapter.SetAREngine(executor);
        }

        public AREnginesType GetCreatedEngine()
        {
            return m_adapter.GetCreatedEngine();
        }
    }

    public enum AREnginesType
    {
        NONE = 0,
        HUAWEI_AR_ENGINE = 1,
        GOOGLE_AR_CORE = 2,
    }
    public enum AREnginesAvaliblity
    {
        NONE_SUPPORTED = 0,
        HUAWEI_AR_ENGINE = 1<<0,
        GOOGLE_AR_CORE = 1<<1,
        ALL_SUPPORTED = HUAWEI_AR_ENGINE| GOOGLE_AR_CORE,
    }
}
