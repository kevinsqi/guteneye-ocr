import OcrModule from './OcrModule'
import type { PaddleOcrOptions, TextLine, DetectionResult } from './types'

/**
 * PaddleOCR v5 wrapper for React Native
 *
 * Provides high-accuracy text detection and recognition using PP-OCRv5 models
 * running on ONNX Runtime.
 *
 * @example
 * ```typescript
 * import { PaddleOcr } from '@gutenye/paddleocr-react-native'
 *
 * // Initialize with default bundled models
 * const ocr = await PaddleOcr.create({})
 *
 * // Detect text in an image
 * const result = await ocr.detect('/path/to/image.jpg')
 *
 * for (const line of result.lines) {
 *   console.log(`${line.text} (${line.score}) at [${line.frame.left}, ${line.frame.top}]`)
 * }
 * ```
 */
export class PaddleOcr {
  private constructor() {}

  /**
   * Create a new PaddleOcr instance
   *
   * @param options - Configuration options
   * @returns A Promise that resolves to a PaddleOcr instance
   */
  static async create(options: PaddleOcrOptions = {}): Promise<PaddleOcr> {
    const nativeOptions: Record<string, unknown> = {}

    if (options.models) {
      nativeOptions.models = {
        detectionPath: options.models.detectionPath,
        recognitionPath: options.models.recognitionPath,
        dictionaryPath: options.models.dictionaryPath,
      }
    }

    if (options.isDebug !== undefined) {
      nativeOptions.isDebug = options.isDebug
    }
    if (options.detectionMaxSize !== undefined) {
      nativeOptions.detectionMaxSize = options.detectionMaxSize
    }
    if (options.detectionThreshold !== undefined) {
      nativeOptions.detectionThreshold = options.detectionThreshold
    }
    if (options.detectionBoxThreshold !== undefined) {
      nativeOptions.detectionBoxThreshold = options.detectionBoxThreshold
    }
    if (options.detectionUnclipRatio !== undefined) {
      nativeOptions.detectionUnclipRatio = options.detectionUnclipRatio
    }
    if (options.detectionUseDilate !== undefined) {
      nativeOptions.detectionUseDilate = options.detectionUseDilate
    }
    if (options.detectionUsePolygonScore !== undefined) {
      nativeOptions.detectionUsePolygonScore = options.detectionUsePolygonScore
    }
    if (options.recognitionImageHeight !== undefined) {
      nativeOptions.recognitionImageHeight = options.recognitionImageHeight
    }

    await OcrModule.create(nativeOptions)
    return new PaddleOcr()
  }

  /**
   * Detect and recognize text in an image
   *
   * @param imagePath - Path to the image file (can start with 'file://')
   * @returns A Promise that resolves to a DetectionResult containing detected text lines
   */
  async detect(imagePath: string): Promise<DetectionResult> {
    // Remove file:// prefix if present
    const normalizedPath = imagePath.replace('file://', '')
    const lines = await OcrModule.detect(normalizedPath)
    return { lines: lines as TextLine[] }
  }
}
