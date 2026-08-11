# @gutenye/paddleocr-react-native

PaddleOCR for React Native using ONNX Runtime. High-accuracy text detection and recognition.

## Installation

```bash
npm install @gutenye/paddleocr-react-native
# or
yarn add @gutenye/paddleocr-react-native
```

## Usage

```typescript
import { PaddleOcr } from '@gutenye/paddleocr-react-native'

// Initialize with default bundled models (PP-OCRv4)
const ocr = await PaddleOcr.create({})

// Or use custom models (e.g., PP-OCRv5 from Hugging Face)
const ocr = await PaddleOcr.create({
  models: {
    detectionPath: '/path/to/det.onnx',
    recognitionPath: '/path/to/rec.onnx',
    dictionaryPath: '/path/to/dict.txt',
  }
})

// Detect text in an image
const result = await ocr.detect('/path/to/image.jpg')

for (const line of result.lines) {
  console.log(`Text: ${line.text}`)
  console.log(`Score: ${line.score}`)
  console.log(`Box: (${line.frame.left}, ${line.frame.top}, ${line.frame.width}, ${line.frame.height})`)
}
```

## Options

```typescript
interface PaddleOcrOptions {
  // Custom model paths
  models?: {
    detectionPath?: string
    recognitionPath?: string
    dictionaryPath?: string
  }
  // Enable debug logging (default: false)
  isDebug?: boolean
  // Maximum image size for detection (default: 960, -1 to disable)
  detectionMaxSize?: number
  // Detection threshold (default: 0.3)
  detectionThreshold?: number
  // Box threshold for filtering (default: 0.5)
  detectionBoxThreshold?: number
  // Unclip ratio for box expansion (default: 1.6)
  detectionUnclipRatio?: number
  // Use dilation (default: false)
  detectionUseDilate?: boolean
  // Use polygon score (default: true)
  detectionUsePolygonScore?: boolean
  // Recognition image height (default: 48)
  recognitionImageHeight?: number
}
```

## Models

### Default Models (PP-OCRv4)
The package includes PP-OCRv4 models by default, which are automatically downloaded during build. These models support Chinese and English text.

### Using PP-OCRv5 Models
For better accuracy, you can use PP-OCRv5 models from Hugging Face:

```bash
# Download from https://huggingface.co/monkt/paddleocr-onnx
# - detection/v5/det.onnx (84MB)
# - languages/english/rec.onnx
# - languages/english/dict.txt
```

Then provide the paths when creating the OCR instance:

```typescript
const ocr = await PaddleOcr.create({
  models: {
    detectionPath: '/path/to/v5/det.onnx',
    recognitionPath: '/path/to/v5/rec.onnx',
    dictionaryPath: '/path/to/v5/dict.txt',
  }
})
```

## Platform Support

- Android: Full support via ONNX Runtime C++ and OpenCV
- iOS: Not yet implemented (contributions welcome!)

## Requirements

- React Native >= 0.71
- Android SDK >= 24

## License

MIT
