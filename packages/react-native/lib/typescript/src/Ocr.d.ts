import type { OcrOptions, TextLine } from './types';
export declare class Ocr {
    static create(options: OcrOptions): Promise<Ocr>;
    detect(rawImagePath: string): Promise<TextLine[]>;
}
//# sourceMappingURL=Ocr.d.ts.map