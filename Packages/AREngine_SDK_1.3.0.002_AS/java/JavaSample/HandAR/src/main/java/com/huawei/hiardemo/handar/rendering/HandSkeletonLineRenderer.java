package com.huawei.hiardemo.handar.rendering;

import android.content.Context;
import android.opengl.GLES20;
import android.util.Log;

import com.huawei.hiar.ARHand;
import com.huawei.hiardemo.handar.R;

import java.nio.FloatBuffer;
import java.util.Collection;

/**
 * Created by x00436406 on 2018/4/10.
 */

public class HandSkeletonLineRenderer {
    private static final String TAG = "HandskeletonLineRenderer";

    private static final int BYTES_PER_FLOAT = Float.SIZE / 8;
    private static final int FLOATS_PER_POINT = 3;  // X,Y,Z,confidence.
    private static final int BYTES_PER_POINT = BYTES_PER_FLOAT * FLOATS_PER_POINT;
    private static final int INITIAL_BUFFER_POINTS = 150;

    private int mVbo;
    private int mVboSize;

    private int mProgramName;
    private int mPositionAttribute;
    private int mModelViewProjectionUniform;
    private int mColorUniform;
    private int mPointSizeUniform;

    private int mNumPoints = 0;
    private int mPointsLineNum = 0;
    private FloatBuffer mLinePoints;

    public void createOnGlThread(Context context) {
        ShaderHelper.checkGLError(TAG, "before create");

        int buffers[] = new int[1];
        GLES20.glGenBuffers(1, buffers, 0);
        mVbo = buffers[0];
        GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, mVbo);

        mVboSize = INITIAL_BUFFER_POINTS * BYTES_PER_POINT;
        GLES20.glBufferData(GLES20.GL_ARRAY_BUFFER, mVboSize, null, GLES20.GL_DYNAMIC_DRAW);
        GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, 0);

        ShaderHelper.checkGLError(TAG, "buffer alloc");

        int vertexShader = ShaderHelper.loadGLShader(TAG, context,
                GLES20.GL_VERTEX_SHADER, R.raw.line_hand_vertex);
        int passthroughShader = ShaderHelper.loadGLShader(TAG, context,
                GLES20.GL_FRAGMENT_SHADER, R.raw.passthrough_fragment);

        mProgramName = GLES20.glCreateProgram();
        GLES20.glAttachShader(mProgramName, vertexShader);
        GLES20.glAttachShader(mProgramName, passthroughShader);
        GLES20.glLinkProgram(mProgramName);
        GLES20.glUseProgram(mProgramName);

        ShaderHelper.checkGLError(TAG, "program");

        mPositionAttribute = GLES20.glGetAttribLocation(mProgramName, "a_Position");
        mColorUniform = GLES20.glGetUniformLocation(mProgramName, "u_Color");
        mModelViewProjectionUniform = GLES20.glGetUniformLocation(
                mProgramName, "u_ModelViewProjection");
        mPointSizeUniform = GLES20.glGetUniformLocation(mProgramName, "u_PointSize");

        ShaderHelper.checkGLError(TAG, "program  params");
    }

    /**
     * Updates the OpenGL buffer contents to the provided point.  Repeated calls with the same
     * point cloud will be ignored.
     */
    public void update() {

        //performanceHelper.printLogIfUpdate("point cloud timestamp: " + cloud.getTimestampNs(), POINT_CLOUD, Long.toString(cloud.getTimestampNs()));
        ShaderHelper.checkGLError(TAG, "before update");
        GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, mVbo);

        mNumPoints = mPointsLineNum;

        if (mNumPoints * BYTES_PER_POINT > mVboSize) {
            while (mNumPoints * BYTES_PER_POINT > mVboSize) {
                mVboSize *= 2;
            }
            GLES20.glBufferData(GLES20.GL_ARRAY_BUFFER, mVboSize, null, GLES20.GL_DYNAMIC_DRAW);
        }

        Log.d(TAG, "skeleton.getSkeletonLinePointsNum()" + mNumPoints);
        Log.d(TAG, "Skeleton Line Points: " + mLinePoints.toString());

        GLES20.glBufferSubData(GLES20.GL_ARRAY_BUFFER, 0, mNumPoints * BYTES_PER_POINT,
                //body.getSkeletonLinePoints());
                mLinePoints);
        GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, 0);

        ShaderHelper.checkGLError(TAG, "after update");
    }

    /**
     * Renders the body Skeleton.
     */
    public void draw(float[] projmtx) {

        ShaderHelper.checkGLError(TAG, "Before draw");

        GLES20.glUseProgram(mProgramName);
        GLES20.glEnableVertexAttribArray(mPositionAttribute);
        GLES20.glEnableVertexAttribArray(mColorUniform);
        GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, mVbo);
        GLES20.glLineWidth(18.0f);
        GLES20.glVertexAttribPointer(
                mPositionAttribute, 4, GLES20.GL_FLOAT, false, BYTES_PER_POINT, 0);
        GLES20.glUniform4f(mColorUniform, 255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 1.0f);
        GLES20.glUniformMatrix4fv(mModelViewProjectionUniform, 1, false, projmtx, 0);
        GLES20.glUniform1f(mPointSizeUniform, 100.0f);

        GLES20.glDrawArrays(GLES20.GL_LINES, 0, mNumPoints);
        GLES20.glDisableVertexAttribArray(mPositionAttribute);
        GLES20.glDisableVertexAttribArray(mColorUniform);
        GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, 0);

        ShaderHelper.checkGLError(TAG, "Draw");
    }

    public void updateData(Collection<ARHand> hands,float[] projmtx) {
        Log.d(TAG, "updateData: ");
        for (ARHand hand : hands) {
            //if (hand.getTrackingState() == ARTrackingState.TRACKING) { //comment for test fake data
            if(hand.getHandskeletonArray().length <= 0
                    || hand.getHandSkeletonConnection().length <= 0) {
                return;
            }
            if (calcSkeletonPoints(hand)) {
                this.update();
                this.draw(projmtx);
            }
            //}
        }
    }

    public boolean calcSkeletonPoints(ARHand arHand) {
        float coor[] = arHand.getHandskeletonArray();
        int connec[] = arHand.getHandSkeletonConnection();
//        Log.d(TAG, "calcSkeletonPoints: connec="+ Arrays.toString(connec));
        if (coor.length <= 0 || connec.length <= 0) {
            return false;
        }
//        for(int i=0;i<coor.length/3;i++){
//            coor[3*i+2]=0.0f;
//        }
        this.mPointsLineNum = 0;
        float linePoint[] = new float[connec.length * 3 * 2];
        for (int j = 0; j < connec.length; j += 2) {
//            Log.d(TAG, "calcSkeletonPoints: j+"+j);
            linePoint[this.mPointsLineNum * 3] = coor[3 * connec[j]];
            linePoint[this.mPointsLineNum * 3 + 1] = coor[3 * connec[j] + 1];
            linePoint[this.mPointsLineNum * 3 + 2] = coor[3 * connec[j] + 2];

            linePoint[this.mPointsLineNum * 3 + 3] = coor[3 * connec[j + 1]];
            linePoint[this.mPointsLineNum * 3 + 4] = coor[3 * connec[j + 1] + 1];
            linePoint[this.mPointsLineNum * 3 + 5] = coor[3 * connec[j + 1] + 2];
            this.mPointsLineNum += 2;
        }
        this.mLinePoints = FloatBuffer.wrap(linePoint);
        return true;
    }
}
