import OcrModule from './OcrModule';
export class Ocr {
  // default options is at shared.h
  static async create(options) {
    await OcrModule.create(options);
    return new Ocr();
  }
  detect(rawImagePath) {
    const imagePath = rawImagePath.replace('file://', '');
    return OcrModule.detect(imagePath);
  }
}
//# sourceMappingURL=Ocr.js.map