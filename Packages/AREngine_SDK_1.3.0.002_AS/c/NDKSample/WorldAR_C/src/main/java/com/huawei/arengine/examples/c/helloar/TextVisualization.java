package com.huawei.arengine.examples.c.helloar;

import com.huawei.hiar.ARBody;

/**
 * Created by j00428315 on 2018/7/20.
 */

public class TextVisualization {
    TextVisualization(){

    }
    private OnTextInfoChangeListener mTextInfoListener;

    public void setListener(OnTextInfoChangeListener listener) {
        this.mTextInfoListener = listener;
    }

    public void updateData(float fpsResult) {
        StringBuilder sb = new StringBuilder();
        sb.append("FPS="+fpsResult);
        sb.append("\n");
        showTextInfo(sb.toString());
    }
    public interface OnTextInfoChangeListener {
        public boolean textInfoChanged(String text, float positionX, float positionY);
    }

    private void showTextInfo(String text) {

        if (mTextInfoListener != null) {
            mTextInfoListener.textInfoChanged(text, 0, 0);
        }
    }

}
