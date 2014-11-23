set nocompatible
syntax on
set hlsearch
set incsearch
set backspace=indent,eol,start
set whichwrap=b,s,<,>,[,]
set number
filetype plugin indent on

let g:tex_flavor='latex'

set shiftwidth=4
set tabstop=4
set expandtab
set smarttab
set softtabstop=4
set cindent

set encoding=utf-8
set fileencodings=utf-8,gb2312,gbk,big5,ucs-bom,cp936,gb18030,latin1
set fileencoding=utf-8
set termencoding=utf-8

set fileformats=unix,dos,mac

set clipboard=unnamed

au BufReadPost * if line("'\"") > 0|if line("'\"")
    \ <= line("$")|exe("norm '\"")|else|exe "norm $"|endif|endif

if has("autocmd")
    autocmd FileType python setlocal et sta sw=2 ts=2 sts=2
    autocmd FileType verilog setlocal et sta sw=2 ts=2 sts=2
endif

if (&t_Co == 256 || &t_Co == 88) && !has('gui_running')
    colorscheme eveninggui
endif

function! Compile()
    if &filetype == "tex"
        execute "!xelatex %"
    else
        let mp = &makeprg
        let ef = &errorformat
        let sil = 1

        if &filetype == "c"
            let &makeprg = "cc -g -o %< -Wall %"
        elseif &filetype == "cpp"
            let &makeprg = "c++ -g -o %< -Wall %"
        elseif &filetype == "java"
            let &makeprg = "javac -Xlint %"
            set errorformat=%A%f:%l:\ %m,%-Z%p^,%-C%.%#
        else
            let &makeprg = "make"
            let sil = 0
        endif

        if sil == 1
            echo 'Compiling ' . expand('%')
        endif

        let curr_dir = expand('%:h')
        if curr_dir == ''
            let curr_dir = '.'
        endif
        execute 'lcd ' . curr_dir
        if sil == 0
            make
        else
            silent make
        endif
        execute ':cwindow'
        execute 'lcd -'
        redraw!

        let &errorformat = ef
        let &makeprg = mp
    endif
endfunction

noremap <F9> :update<CR>:call Compile()<CR>
noremap <F10> :cnext<CR>
noremap <F11> :cprevious<CR>

function! Run()
    let curr_dir = expand('%:h')
    if curr_dir == ''
        let curr_dir = '.'
    endif
    let filename = expand('%:t:r')

    execute 'lcd ' . curr_dir

    if filereadable(filename . ".in")
        let input = 1
    else
        let input = 0
    endif

    if &filetype=="java"
        if input == 0
            execute "!java " . filename
        else
            execute "!java " . filename . " < " . filename . ".in"
        endif
    elseif &filetype=="tex"
        execute "!evince " . filename . '.pdf'
    elseif &filetype=="python"
        execute 'update'
        execute "!%"
    elseif &filetype=="cpp" || &filetype=="c"
        if input == 0
            execute "!" . filename
        else
            execute "!" . filename . " < " . filename . ".in"
        endif
    else
        execute "!" . filename
    endif
    execute 'lcd -'
endfunction

noremap <F5> :call Run()<CR>

nnoremap j gj
nnoremap k gk
nnoremap tn :tabnew<Space>
