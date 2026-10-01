# ReadAloud ðŸ“–ðŸ”Š

A web application that transforms PDF documents into **editable text or spoken audio** through OCR and text-to-speech processing.

ReadAloud combines a Flask backend with an interactive web interface and provides two main tools:

- ðŸ”Ž **Enchanted Vision** â€” extracts editable text from scanned or image-based PDFs using OCR.
- ðŸ”Š **Sorcerer's Voice** â€” converts uploaded PDF documents or directly entered text into speech.

## Preview

### Home

<p align="center">
  <img src="docs/screenshots/home.png" width="850" alt="ReadAloud homepage">
</p>

### OCR — PDF to Editable Text

<p align="center">
  <img src="docs/screenshots/ocr-upload.png" width="45%" alt="PDF upload interface">
  &nbsp;&nbsp;
  <img src="docs/screenshots/ocr-result.png" width="45%" alt="OCR extracted text">
</p>

### Text-to-Speech

<p align="center">
  <img src="docs/screenshots/tts-input.png" width="45%" alt="Direct text input">
  &nbsp;&nbsp;
  <img src="docs/screenshots/tts-player.png" width="45%" alt="Generated audio player">
</p>

## Features

### ðŸ”Ž PDF â†’ Text

- Drag-and-drop PDF upload
- PDF-to-image conversion
- OCR with Tesseract
- Extracted text displayed directly in the browser
- Copy extracted text to clipboard

### ðŸ”Š Text / PDF â†’ Speech

- Convert typed text to speech
- Extract text from PDF documents
- Generate audio using Google Cloud Text-to-Speech
- Integrated HTML5 audio player
- Download generated audio

## Tech Stack

**Backend**

- Python
- Flask
- Flask-SocketIO

**Document Processing**

- PyPDF2
- Tesseract OCR
- pdf2image

**Text-to-Speech**

- Google Cloud Text-to-Speech API

**Frontend**

- HTML
- CSS
- JavaScript
- Bootstrap
- Socket.IO

## Architecture

```text
                         â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                         â”‚   ReadAloud   â”‚
                         â”‚ Web Interface â”‚
                         â””â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”˜
                                 â”‚
                    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                    â”‚                         â”‚
               OCR workflow              TTS workflow
                    â”‚                         â”‚
                 PDF input              Text / PDF input
                    â”‚                         â”‚
                 pdf2image                  PyPDF2
                    â”‚                         â”‚
                 Tesseract                    â”‚
                    â”‚                         â”‚
               Extracted text â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                    â”‚
                    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–º Google Cloud TTS
                                           â”‚
                                           â–¼
                                       MP3 audio
```

## Running Locally

### Requirements

Besides the Python dependencies, the OCR functionality requires:

- **Tesseract OCR**
- **Poppler**
- a **Google Cloud Text-to-Speech API key** for speech generation

Clone the repository:

```bash
git clone https://github.com/Schwarz28Iva/ReadAloud-Document-Helper.git
cd ReadAloud-Document-Helper
```

Install the Python dependencies:

```bash
pip install -r requirements.txt
```

Create a local `.env` file based on `.env.example`:

```text
GOOGLE_TTS_API_KEY=your_api_key_here
```

If Tesseract is not available on your PATH, also configure:

```text
TESSERACT_CMD=path_to_tesseract
```

Run the application:

```bash
python server.py
```

Then open the local address displayed by Flask in your browser.

## Project Motivation

ReadAloud was built as an exploration of document accessibility and transformation: making content available both as editable text and spoken audio through a single visual interface.

The project also provided hands-on experience integrating document processing, OCR, external APIs, WebSockets, backend services, and frontend interaction into one end-to-end application.

## Notes

- Uploaded documents are processed by the application and are not intended to be committed to the repository.
- Generated audio files are ignored by Git.
- API keys and local environment settings belong in `.env`, which is ignored by Git.

## Possible Improvements

- Add automated tests for the processing services and API routes
- Improve OCR language selection
- Add configurable text-to-speech voices and languages
- Improve accessibility and responsive behavior
- Add deployment configuration for a hosted demo

