/**
 * Options for initializing PaddleOCR
 */
export interface PaddleOcrOptions {
  /**
   * Custom model paths. If not provided, bundled PP-OCRv5 models are used.
   */
  models?: {
    /** Path to the detection ONNX model */
    detectionPath?: string
    /** Path to the recognition ONNX model */
    recognitionPath?: string
    /** Path to the character dictionary file */
    dictionaryPath?: string
  }
  /** Enable debug logging */
  isDebug?: boolean
  /** Maximum image size for detection (default: 960, -1 to disable) */
  detectionMaxSize?: number
  /** Detection threshold for binarization (default: 0.3) */
  detectionThreshold?: number
  /** Box threshold for filtering detections (default: 0.5) */
  detectionBoxThreshold?: number
  /** Unclip ratio for box expansion (default: 1.6) */
  detectionUnclipRatio?: number
  /** Use dilation on detection output (default: false) */
  detectionUseDilate?: boolean
  /** Use polygon score for filtering (default: true) */
  detectionUsePolygonScore?: boolean
  /** Recognition image height (default: 48 for PP-OCRv5) */
  recognitionImageHeight?: number
}

/**
 * Bounding box frame for detected text
 */
export interface Frame {
  /** Top Y coordinate */
  top: number
  /** Left X coordinate */
  left: number
  /** Width of the bounding box */
  width: number
  /** Height of the bounding box */
  height: number
}

/**
 * A single line of detected/recognized text
 */
export interface TextLine {
  /** The recognized text content */
  text: string
  /** Confidence score (0-1) */
  score: number
  /** Bounding box coordinates */
  frame: Frame
}

/**
 * Result from the detect method
 */
export interface DetectionResult {
  /** Array of detected text lines */
  lines: TextLine[]
}
