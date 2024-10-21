colorscheme vim
set nocompatible            " disable compatibility to old-time vi
set showmatch               " show matching brackets.
set ignorecase              " case insensitive matching
set mouse=nv                " enable mouse in normal and visual mode
set hlsearch                " highlight search results
set autoindent              " indent a new line the same amount as the line just typed
set number                  " add line numbers
set ruler                   " Always display the current cursor position in the lower right corner of the Vim window.
syntax on
set wildmode=longest,list   " get bash-like tab completions
set cc=88                   " set colour columns for good coding style
filetype plugin indent on   " allows auto-indenting depending on file type
set tabstop=4               " number of columns occupied by a tab character
set expandtab               " convert tabs to white space
set shiftwidth=4            " width for autoindents
set softtabstop=4           " see multiple spaces as tabstops so <BS> does the right thing
" set spell
set cursorline
"hi CursorLine term=underline cterm=NONE gui=NONE ctermbg=17
set rulerformat +=%L
set colorcolumn=0

set virtualedit=block

set makeprg=./build.sh

map <silent> <F2> :set rnu! <CR>" toggle relative numbers 
map <silent> <F3> :nohls <CR>
nnoremap <F4> <ESC> 0i//<ESC>j
nnoremap \ $h 
inoremap <F4> <ESC> 0i//<ESC>ji
nnoremap k gk
nnoremap <Up> gk
nnoremap j gj
nnoremap <Down> gj
inoremap <C-Del> <ESC> dw hi
inoremap <S-Del> <ESC> dw hi
inoremap  

"augroup numbertoggle
"    autocmd!
"    autocmd BufEnter,FocusGained,InsertLeave,WinEnter * if mode() == 'v' | set rnu   | endif
"    autocmd BufLeave,FocusLost,InsertEnter,WinLeave   *                  | set nornu | endif
"augroup END

call plug#begin(stdpath('data') . '/plugged')

call plug#end()
