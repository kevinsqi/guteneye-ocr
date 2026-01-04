package com.paddleocr

import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.bridge.ReactMethod
import java.io.File
import java.io.FileOutputStream

const val BUNDLE_DIR = "paddleocr.bundle"
const val OUTPUT_DIR = "paddleocr.outputs"

class RNPaddleOcrModule internal constructor(private val context: ReactApplicationContext) :
    RNPaddleOcrSpec(context) {
  companion object {
    const val NAME = "RNPaddleOcr"

    init {
      System.loadLibrary("paddleocr")
    }
  }

  external fun nativeInstall(jsiPtr: Long, assetDir: String, debugOutputDir: String)

  override fun getName(): String {
    return NAME
  }

  override fun initialize() {
    copyAssetToCacheDir()
    install()
  }

  @ReactMethod(isBlockingSynchronousMethod = true)
  override fun install() {
    try {
      val jsContext = getReactApplicationContext().getJavaScriptContextHolder()

      if (jsContext === null || jsContext.get() == 0L) {
        println("PaddleOCR: JSI Runtime is not available in legacy chrome console")
        return
      }

      val assetDir = "${context.cacheDir}/${BUNDLE_DIR}"
      val debugOutputDir = "${context.cacheDir}/${OUTPUT_DIR}"
      nativeInstall(jsContext.get(), assetDir, debugOutputDir)
    } catch (exception: Exception) {
      println("PaddleOCR: $exception")
    }
  }

  private fun copyAssetToCacheDir() {
    val assetManager = context.assets
    val fileNames = assetManager.list(BUNDLE_DIR) ?: arrayOf()
    for (fileName in fileNames) {
      val srcFile = "$BUNDLE_DIR/$fileName"
      val destDir = File("${context.cacheDir}/$BUNDLE_DIR")
      destDir.mkdirs()
      val destFile = File("$destDir/$fileName")
      if (destFile.exists()) {
        continue
      }
      assetManager.open(srcFile).use { inputStream ->
        FileOutputStream(destFile).use { outputStream -> inputStream.copyTo(outputStream) }
      }
    }
  }
}
