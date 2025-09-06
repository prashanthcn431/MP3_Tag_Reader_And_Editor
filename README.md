# MP3_Tag_Reader_And_Editor

<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8" />
  <title>MP3 Tag Reader &amp; Editor (ID3v2.3) — README</title>
  <style>
    body { font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial; line-height:1.6; padding: 24px; color:#222; }
    pre { background:#f6f8fa; border:1px solid #e1e4e8; padding:12px; overflow:auto; }
    code { background:#f1f1f1; padding:2px 6px; border-radius:4px; }
    h1,h2 { color:#0b5fff; }
    .meta { color:#555; }
    ul.features { margin-left: 1.1rem; }
    .files li { margin: 6px 0; }
  </style>
</head>
<body>

  <h1>MP3 Tag Reader &amp; Editor (ID3v2.3)</h1>
  <p class="meta">
    Terminal-based MP3 metadata reader and editor written in <strong>C</strong>. Reads and edits ID3v2 tags (targeting ID3v2.3.0).  
    Developed as part of the Certified Embedded Professional (ECEP) course at Emertxe Information Technologies, Bangalore.
  </p>

  <h2>Project Highlights</h2>
  <ul class="features">
    <li>View MP3 metadata: <em>Title, Artist, Album, Year, Genre, Composer, Lyricist, Comments</em>.</li>
    <li>Edit specific metadata frames (creates a modified copy of the MP3 with the updated tag).</li>
    <li>Primary support for ID3v2.3.0; partial/limited support for earlier versions only (v2.4 excluded).</li>
    <li>Command-line interface for quick operations.</li>
    <li>Modular C implementation with separate source and header files for readability and reuse.</li>
  </ul>

  <h2>Supported Tag Frames (examples)</h2>
  <ul>
    <li><code>TIT2</code> — Title</li>
    <li><code>TPE1</code> — Artist</li>
    <li><code>TALB</code> — Album</li>
    <li><code>TYER</code> — Year</li>
    <li><code>TCON</code> — Genre</li>
    <li><code>COMM</code> — Comment / Composer field used here</li>
  </ul>

  <h2>Project Structure</h2>
  <ul class="files">
    <li><strong>mp3_tagreader.c</strong> — CLI &amp; program flow, argument parsing, edit flow (creates <code>temp.mp3</code>, replaces original on success). :contentReference[oaicite:0]{index=0}</li>
    <li><strong>function.c</strong> — Core reading/parsing functions: <code>read_tags()</code>, <code>copy_remain()</code>, and <code>check_id3_version()</code>. These functions handle frame reads/writes and endian conversions. :contentReference[oaicite:1]{index=1}</li>
    <li><strong>header_file.h</strong> — Header declarations for the reading/editing functions. :contentReference[oaicite:2]{index=2}</li>
    <li><strong>Makefile</strong> — (Optional) build automation (if present in your repo). If not present, compile via <code>gcc</code> command below.</li>
    <li><strong>README.md</strong> — This file (HTML content allowed inside README on many platforms).</li>
  </ul>

  <h2>Build</h2>
  <p>If a <code>Makefile</code> exists, simply run:</p>
  <pre><code>make</code></pre>
  <p>Or compile manually (example):</p>
  <pre><code>gcc -o mp3_reader mp3_tagreader.c function.c</code></pre>
  <p>If compiled without the <code>-o</code> option the produced binary will be <code>a.out</code>, which the original code's help messages reference. :contentReference[oaicite:3]{index=3}</p>

  <h2>Usage</h2>
  <p>View tags</p>
  <pre><code>./mp3_reader -v &lt;filename.mp3&gt;</code></pre>
  <p>Edit a tag</p>
  <pre><code>./mp3_reader -e &lt;filename.mp3&gt; &lt;tag_option&gt; &lt;new_value&gt;</code></pre>
  <p>Tag options (as implemented):</p>
  <pre><code>-t  Title
-a  Artist
-A  Album
-y  Year
-c  Composer (uses COMM frame)
-g  Genre
-h  Help</code></pre>

  <h2>Example</h2>
  <p>Viewing tags</p>
  <pre><code>./mp3_reader -v song.mp3

----- MP3 TAGS -----
Title   :    Shape of You
Artist  :    Ed Sheeran
Album   :    ÷ (Divide)
Year    :    2017
Genre   :    Pop
Composer:    Ed Sheeran
</code></pre>

  <p>Editing title (example):</p>
  <pre><code>./mp3_reader -e song.mp3 -t "New Song Title"

INFO: Editing Tag...
INFO: Writing new value to frame TIT2 (Title)
INFO: Tag updated successfully!
</code></pre>

  <h2>How it works (high-level)</h2>
  <ol>
    <li><strong>Header &amp; Version Check:</strong> The program checks the first 3 bytes for the "ID3" header, reads the two version bytes and only proceeds for ID3v2.3.0. (See <code>check_id3_version()</code> in <code>function.c</code>.) :contentReference[oaicite:4]{index=4}</li>
    <li><strong>Frame scanning:</strong> The reader moves into the ID3 tag block and iterates over known frames (e.g., TIT2, TPE1, TALB, TYER, TCON, COMM) to extract the stored text. The reading routine fills fixed buffers (Title, Artist, Album, Year, etc.). :contentReference[oaicite:5]{index=5}</li>
    <li><strong>Editing:</strong> When updating a single frame, the program creates a temporary output file (<code>temp.mp3</code>), copies the ID3 header, and for each frame either writes the original content or writes the replaced value for the target frame. After a successful write, the original file is deleted and the temp file is renamed back to the original filename. (Flow in <code>mp3_tagreader.c</code>.) :contentReference[oaicite:6]{index=6}</li>
    <li><strong>Endian handling:</strong> Frame sizes in ID3v2 are read and byte-swapped as required by the implementation before reading/writing. See the endian handling macros / code in <code>function.c</code>. :contentReference[oaicite:7]{index=7}</li>
  </ol>

  <h2>Implementation notes &amp; limitations</h2>
  <ul>
    <li>Supports and expects <strong>ID3v2.3.0</strong>. Attempting to edit unsupported versions will be rejected by the version check. :contentReference[oaicite:8]{index=8}</li>
    <li>Frame-handling loop is implemented for a fixed number of frames in the provided code (reads up to 6 frames). If tags are arranged differently or additional frames are present, you may need to extend parsing logic. :contentReference[oaicite:9]{index=9}</li>
    <li>The current code uses fixed-size buffers for tag contents (e.g., 50–100 bytes). Very long tag values may be truncated; consider dynamic allocation for robust handling of large values. :contentReference[oaicite:10]{index=10}</li>
    <li>Text encoding: the code assumes simple ASCII/ISO-8859-1 textual frames. For full Unicode (UTF-16/UTF-8) support, the frame encoding byte must be checked and converted properly.</li>
    <li>Backup: The editor overwrites the original file after creating <code>temp.mp3</code>. Keep backups of original files when testing. :contentReference[oaicite:11]{index=11}</li>
  </ul>

  <h2>Troubleshooting</h2>
  <ul>
    <li><strong>File not opening:</strong> Ensure the MP3 exists and you have read/write permissions.</li>
    <li><strong>Unsupported ID3 version:</strong> The program explicitly checks and reports unsupported versions (only v2.3 allowed). :contentReference[oaicite:12]{index=12}</li>
    <li><strong>Incorrect command usage:</strong> Run with no args or <code>-help</code> to show usage: the help text is printed from <code>mp3_tagreader.c</code>. :contentReference[oaicite:13]{index=13}</li>
  </ul>

  <h2>Contributing</h2>
  <p>To improve this tool, consider:</p>
  <ul>
    <li>Adding proper UTF-16/UTF-8 handling for ID3 text frames.</li>
    <li>Parsing the entire tag header size properly and iterating until end-of-tag rather than a fixed frame count.</li>
    <li>Replacing fixed buffers with safe dynamic allocations and boundary checks.</li>
    <li>Adding unit tests for parsing/writing frames.</li>
  </ul>

  <h2>References &amp; Source</h2>
  <p>Key source files in this repo: <code>mp3_tagreader.c</code> (CLI &amp; orchestration), <code>function.c</code> (parsing/editing functions) and <code>header_file.h</code> (declarations). :contentReference[oaicite:14]{index=14} :contentReference[oaicite:15]{index=15} :contentReference[oaicite:16]{index=16}</p>

  <h2>License</h2>
  <p>Use as you like for learning and experimentation. Consider adding an explicit license file (e.g., <code>LICENSE</code>) such as MIT if you want to permit reuse.</p>

 
