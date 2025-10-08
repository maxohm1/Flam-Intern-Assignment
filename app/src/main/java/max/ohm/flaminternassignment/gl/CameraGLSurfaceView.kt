package max.ohm.flaminternassignment.gl

import android.content.Context
import android.graphics.Bitmap
import android.opengl.GLES20
import android.opengl.GLSurfaceView
import android.util.AttributeSet
import android.util.Log
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class CameraGLSurfaceView @JvmOverloads constructor(
    context: Context,
    attrs: AttributeSet? = null
) : GLSurfaceView(context, attrs) {
    
    private val renderer: CameraRenderer
    
    init {
        setEGLContextClientVersion(2)
        renderer = CameraRenderer()
        setRenderer(renderer)
        renderMode = RENDERMODE_WHEN_DIRTY
    }
    
    fun updateFrame(bitmap: Bitmap) {
        renderer.updateBitmap(bitmap)
        requestRender()
    }
    
    inner class CameraRenderer : Renderer {
        private val textureRenderer = TextureRenderer()
        private var bitmap: Bitmap? = null
        private val lock = Object()
        
        override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
            GLES20.glClearColor(0.0f, 0.0f, 0.0f, 1.0f)
            textureRenderer.initialize()
            Log.i(TAG, "Surface created")
        }
        
        override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
            GLES20.glViewport(0, 0, width, height)
            Log.i(TAG, "Surface changed: $width x $height")
        }
        
        override fun onDrawFrame(gl: GL10?) {
            GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT)
            
            synchronized(lock) {
                bitmap?.let {
                    textureRenderer.updateTexture(it)
                    textureRenderer.draw()
                }
            }
        }
        
        fun updateBitmap(newBitmap: Bitmap) {
            synchronized(lock) {
                bitmap = newBitmap
            }
        }
    }
    
    companion object {
        private const val TAG = "CameraGLSurfaceView"
    }
}

