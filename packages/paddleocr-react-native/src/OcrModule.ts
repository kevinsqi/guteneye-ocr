import { NativeModules, Platform } from 'react-native'

const LINKING_ERROR =
  `The package '@gutenye/paddleocr-react-native' doesn't seem to be linked. Make sure: \n\n` +
  Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
  '- You rebuilt the app after installing the package\n' +
  '- You are not using Expo Go\n'

interface OcrModuleInterface {
  install(): void
  create(options: Record<string, unknown>): Promise<void>
  detect(imagePath: string): Promise<Array<{
    text: string
    score: number
    frame: { top: number; left: number; width: number; height: number }
  }>>
}

const OcrModule: OcrModuleInterface = NativeModules.RNPaddleOcr
  ? NativeModules.RNPaddleOcr
  : new Proxy(
      {},
      {
        get() {
          throw new Error(LINKING_ERROR)
        },
      }
    )

export default OcrModule
