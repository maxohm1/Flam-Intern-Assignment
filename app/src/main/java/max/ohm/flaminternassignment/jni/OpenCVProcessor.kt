package max.ohm.flaminternassignment.jni

import android.graphics.Bitmap
import android.util.Log

class OpenCVProcessor {
    
    companion object {
        private const val TAG = "OpenCVProcessor"
        
        init {
            try {
                System.loadLibrary("opencv_java4")
                System.loadLibrary("opencv_processor")
                Log.i(TAG, "Native libraries loaded successfully")
            } catch (e: UnsatisfiedLinkError) {
                Log.e(TAG, "Failed to load native library: ${e.message}")
            }
        }
    }
    
    // Native method declarations
    external fun applyCannyEdge(inputBitmap: Bitmap, outputBitmap: Bitmap)
    
    external fun convertToGrayscale(inputBitmap: Bitmap, outputBitmap: Bitmap)
    
    external fun invertColors(inputBitmap: Bitmap, outputBitmap: Bitmap)
    
    external fun getOpenCVVersion(): String
    
    // Wrapper functions for easier use
    fun processCannyEdge(input: Bitmap): Bitmap {
        val output = Bitmap.createBitmap(input.width, input.height, Bitmap.Config.ARGB_8888)
        applyCannyEdge(input, output)
        return output
    }
    
    fun processGrayscale(input: Bitmap): Bitmap {
        val output = Bitmap.createBitmap(input.width, input.height, Bitmap.Config.ARGB_8888)
        convertToGrayscale(input, output)
        return output
    }
    
    fun processInvert(input: Bitmap): Bitmap {
        val output = Bitmap.createBitmap(input.width, input.height, Bitmap.Config.ARGB_8888)
        invertColors(input, output)
        return output
    }
}

