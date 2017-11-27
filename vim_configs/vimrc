"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => General
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
 " Sets how many lines of history VIM has to remember
 "set history=700
 set nu

 " Enable filetype plugins
 filetype plugin on
 filetype indent on

 " Set to auto read when a file is changed from the outside
 set autoread

 " With a map leader it's possible to do extra key combinations
 " like <leader>w saves the current file
 let mapleader = ";"
 let g:mapleader = ";"

 " Fast saving
 nmap <leader>w :w!<cr>
 nmap <leader>q :q!<cr>
 nmap <leader>wq :wq!<cr>
 nmap <leader>wqa :wqa!<cr>

:inoremap <C-s> <Esc>:w!<cr>
:inoremap <C-q> <Esc>:q!<cr>

"let vim flag whitespace
"au BufRead,BufNewFile *.py,*.pyw,*.c,*.h match BadWhitespace /\s\+$/
au BufRead *.py set softtabstop=4 shiftwidth=4

let g:ycm_server_keep_logfiles = 1
let g:ycm_server_log_level = 'debug'

 "mapping moving between windows in vim
  noremap <C-`>   <C-W>w

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => VIM user interface
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
 " Set 7 lines to the cursor - when moving vertically using j/1k
 set so=7

 " Turn on the WiLd menu
 set wildmenu

 " Ignore compiled files
 set wildignore=*.o,*~,*.pyc

 "Always show current position
 set ruler

 " Height of the command bar
 set cmdheight=2

 " A buffer becomes hidden when it is abandoned
 set hid

 " Configure backspace so it acts as it should act
 set backspace=eol,start,indent
 set whichwrap+=<,>,h,l

 " Ignore case when searching
 set ignorecase

 " When searching try to be smart about cases 
 set smartcase

 " Highlight search results
 "set hlsearch
 ":hi Search guibg=LightBlue
 let g:highlighting = 0
 function! Highlighting()
     if g:highlighting == 1 && @/ =~ '^\\<'.expand('<cword>').'\\>$'
         let g:highlighting = 0
         return ":silent nohlsearch\<CR>"
     endif
     let @/ = '\<'.expand('<cword>').'\>'
     let g:highlighting = 1
     return ":silent set hlsearch\<CR>"
 endfunction
 nnoremap <silent> <expr> <CR> Highlighting()

 " Makes search act like search in modern browsers
 set incsearch

 " Don't redraw while executing macros (good performance config)
 set lazyredraw

 " For regular expressions turn magic on
 set magic

 " Show matching brackets when text indicator is over them
 set showmatch
 " How many tenths of a second to blink when matching brackets
 set mat=2

 " No annoying sound on errors
 set noerrorbells
 set novisualbell
 set t_vb=
 set tm=500

 """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
 " => Colors and Fonts
 """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
 " Enable syntax highlighting

":colorscheme monokai
let g:molokai_original = 1
let g:rehash256 = 1

 " Set extra options when running in GUI mode
 if has("gui_running")
     set guioptions-=T
     set guioptions+=e
     set t_Co=256
     set guitablabel=%M\ %t
 endif

 " Set utf8 as standard encoding and en_US as the standard language
 set encoding=utf-8

 " Use Unix as the standard file type
 set ffs=unix,dos,mac

 """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
 " => Files, backups and undo
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " Turn backup off, since most stuff is in SVN, git et.c anyway...
  set nobackup
  set nowb
  set noswapfile
 
 
  """"""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => Text, tab and indent related
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " Use spaces instead of tabs
  set expandtab
 
  " Be smart when using tabs ;)
  set smarttab
 
  " 1 tab == 4 spaces
  set shiftwidth=4
  set tabstop=4
 
  " Linebreak on 500 characters
  set lbr
  set tw=500
 
  set ai "Auto indent
  set si "Smart indent
  set wrap "Wrap lines
 

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => Moving around, tabs, windows and buffers
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " Treat long lines as break lines (useful when moving around in them)
  map j gj
  map k gk

  " Map <Space> to / (search) and Ctrl-<Space> to ? (backwards search)
  map <space> /
  map <c-space> ?

  " Disable highlight when <leader><cr> is pressed
  map <silent> <leader><cr> :noh<cr>

  " Smart way to move between windows
  map <C-j> <C-W>j
  map <C-k> <C-W>k
  map <C-h> <C-W>h
  map <C-l> <C-W>l

  " Close the current buffer
  map <leader>bd :Bclose<cr>

  " Close all the buffers
  map <leader>ba :1,1000 bd!<cr>

  " Useful mappings for managing tabs
  map <leader>tn :tabnew<cr>
  map <leader>to :tabonly<cr>
  map <leader>tc :tabclose<cr>
  map <leader>tm :tabmove

  " Opens a new tab with the current buffer's path
  " Super useful when editing files in the same directory
  map <leader>te :tabedit <c-r>=expand("%:p:h")<cr>/

  " Switch CWD to the directory of the open buffer
  map <leader>cd :cd %:p:h<cr>:pwd<cr>

  " Specify the behavior when switching between buffers 
  "try
      "set switchbuf=useopen,usetab,newtab
      "set stal=2
  "catch
  "endtry

  " Return to last edit position when opening files (You want this!)
  "autocmd BufReadPost *
              "\ if line("'\"") > 0 && line("'\"") <= line("$") |
              "\   exe "normal! g`\"" |
              "\ endif
  ";Remember info about open buffers on close
  "set viminfo^=%
  

""""""""""""""""""""""""""""""
" => Status line
""""""""""""""""""""""""""""""
 " Always show the status line
 set laststatus=2

 " Format the status line
 set statusline=\ %{HasPaste()}%F%m%r%h\ %w\ \ CWD:\ %r%{getcwd()}%h\ \ \ Line:\ %l
 function! HasPaste()
     if &paste
         return 'PASTE MODE  '
     en
     return ''
 endfunction


 """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
 " => Editing mappings
 """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
 " Remap VIM 0 to first non-blank character
 map 0 ^

 " Move a line of text using ALT+[jk] or Comamnd+[jk] on mac
 nmap <M-j> mz:m+<cr>`z
 nmap <M-k> mz:m-2<cr>`z
 vmap <M-j> :m'>+<cr>`<my`>mzgv`yo`z
 vmap <M-k> :m'<-2<cr>`>my`<mzgv`yo`z

 if has("mac") || has("macunix")
     nmap <D-j> <M-j>
     nmap <D-k> <M-k>
     vmap <D-j> <M-j>
     vmap <D-k> <M-k>
 endif

 " Delete trailing white space on save, useful for Python and CoffeeScript ;)
 func! DeleteTrailingWS()
     exe "normal mz"
     %s/\s\+$//ge
     exe "normal `z"
 endfunc
 autocmd BufWrite *.py :call DeleteTrailingWS()
 autocmd BufWrite *.coffee :call DeleteTrailingWS()

":set nocp
:syntax on 
execute pathogen#infect()
"call pathogen#runtime_append_all_bundles()
"call pathogen#helptags()
:set autoindent    " always set autoindenting on
:set copyindent    " copy the previous indentation on autoindenting
:set shiftround    " use multiple of shiftwidth when indenting with '<' and '>'
:set showmatch     " set show matching parenthesis
:set ignorecase    " ignore case when searching
:set smartcase     " ignore case if search pattern is all lowercase,
                    "    case-sensitive otherwise
:set smarttab      " insert tabs on the start of a
                   " line according to
                   " shiftwidth, not tabstop
:set mouse=a                   
fun! s:ToggleMouse()
    if !exists("s:old_mouse")
        let s:old_mouse = "a"
    endif

    if &mouse == ""
        let &mouse = s:old_mouse
        echo "Mouse is for Vim (" . &mouse . ")"
    else
        let s:old_mouse = &mouse
        let &mouse=""
        echo "Mouse is for terminal"
    endif
endfunction
                   

"settings for syntastic plugin
"----------------------------------------------------------------------------------------------
set statusline+=%#warningmsg#
set statusline+=%{SyntasticStatuslineFlag()}
set statusline+=%*

let g:syntastic_always_populate_loc_list = 1
let g:syntastic_auto_loc_list = 1
let g:syntastic_check_on_open = 1
let g:syntastic_check_on_wq = 0
let g:syntastic_cpp_check_header = 1
let g:syntastic_c_include_dirs = ['../../include','../include']
let g:syntastic_c_checkers=['make','splint']
let g:syntastic_cpp_compiler_options = ' -std=c++11 -stdlib=libc++'


"nertree plugin settings 
"--------------------------------------------------------------------------------------------------

"Stick this in your vimrc to open NERDTree with Ctrl+n (you can set whatever key you want):

"close vim if the only window left open is a NERDTree
autocmd bufenter * if (winnr("$") == 1 && exists("b:NERDTree") && b:NERDTree.isTabTree()) | q | endif

let g:NERDTreeDirArrowExpandable = '▸'
let g:NERDTreeDirArrowCollapsible = '▾'
let NERDTreeMinimalUI = 1
let g:NERDTreeWinSize=40
let NERDTreeIgnore=['\.pyc$', '\~$'] "ignore files in NERDTree



" Open NERDTree in the directory of the current file (or /home if no file is open)
nmap <silent> <C-i> :call NERDTreeToggleInCurDir()<cr>
function! NERDTreeToggleInCurDir()
    " If NERDTree is open in the current buffer
    if (exists("t:NERDTreeBufName") && bufwinnr(t:NERDTreeBufName) != -1)
        exe ":NERDTreeClose"
    else
        exe ":NERDTreeFind"
    endif
endfunction

"fugitive plugin settings
"----------------------------------------------------------------------------------------------------


"ctrlP plugin settings
"----------------------------------------------------------------------------------------------------
let g:ctrlp_map = '<c-p>'
let g:ctrlp_cmd = 'CtrlP'

set wildignore+=*/tmp/*,*.so,*.swp,*.zip     " MacOSX/Linux
set wildignore+=*\\tmp\\*,*.swp,*.zip,*.exe  " Windows

"let g:ctrlp_custom_ignore = '\v[\/]\.(git|hg|svn)$'
let g:ctrlp_custom_ignore = {
			\ 'dir':  '\v[\/]\.(git|hg|svn)$',
			\ 'file': '\v\.(exe|so|dll)$',
			\ 'link': 'some_bad_symbolic_links',
			\ }
let g:ctrlp_user_command = 'find %s -type f'        " MacOSX/Linux
let g:ctrlp_switch_buffer = 'Et'
let g:ctrlp_working_path_mode = 'w'



"minibuf explorer plugin setting
"----------------------------------------------------------------------------------------------------
"let g:miniBufExplMapWindowNavVim = 1 
"let g:miniBufExplMapWindowNavArrows = 1 
"let g:miniBufExplMapCTabSwitchBufs = 1 
"let g:miniBufExplModSelTarget = 1 
"" move between buffers in vim
"map <F2> :bprevious<CR>
"map <F3> :bnext<CR>

"python indentation
:set tabstop=8 expandtab shiftwidth=4 softtabstop=4

"cscope settings
"autoload cscope database
function! LoadCscope()
    let db = findfile("cscope.out", ".;")
    if (!empty(db))
        let path = strpart(db, 0, match(db, "/cscope.out$"))
        set nocscopeverbose " suppress 'duplicate connection' error
        exe "cs add " . db . " " . path
        set cscopeverbose
    endif
endfunction
au BufEnter /* call LoadCscope()
:set cscopetag

nmap <F10> :!find . -iname '*.c' -o -iname '*.cpp' -o -iname '*.h' -o -iname '*.hpp' -o -iname '*.py' > cscope.files<CR>
  \:!cscope -b -i cscope.files -f cscope.out<CR>
  \:cs add cscope.out<CR>
  \:cs reset<CR>

"Tagbar plugin settings
"---------------------------------------------------------------------------------------------------------
 nnoremap <silent> <F9> :TagbarToggle<CR>
 let g:tagbar_zoomwidth = 0
 let g:tagbar_indent = 1

"You complete me plugin settings
"---------------------------------------------------------------------------------------------------------
let g:ycm_key_list_select_completion=[]
let g:ycm_key_list_previous_completion=[]
let g:ycm_global_ycm_extra_conf = "~/.vim/.ycm_extra_conf.py"

let g:go_disable_autoinstall = 0

" Highlight
 let g:go_highlight_functions = 1  
 let g:go_highlight_methods = 1  
 let g:go_highlight_structs = 1  
 let g:go_highlight_operators = 1  
 let g:go_highlight_build_constraints = 1 

 "neocomplete plugin
 "
 let g:neocomplete#enable_at_startup = 1
 let g:neocomplete#enable_smart_case = 1
 let g:neocomplete#sources#syntax#min_keyword_length = 3
 let g:neocomplete#auto_completion_start_length = 1
 let g:neocomplete#sources#buffer#cache_limit_size = 50000
 let g:neocomplete#data_directory = $HOME.'/.vim/cache/noecompl'
 let g:neocomplete#sources#syntax#min_keyword_length = 3
 if !exists('g:neocomplete#force_omni_input_patterns')
     let g:neocomplete#force_omni_input_patterns = {}
 endif
 let g:neocomplete#force_omni_input_patterns.javascript = '[^. \t]\.\w*'
 " Tab completion.
    inoremap <expr><TAB>  pumvisible() ? "\<C-n>" : "\<TAB>"
 
    aug omnicomplete
        au!
        au FileType css setl omnifunc=csscomplete#CompleteCSS
        au FileType markdown setl omnifunc=htmlcomplete#CompleteTags
        au FileType html,htmldjango,jinja setl omnifunc=emmet#completeTag
        au FileType javascript setl omnifunc=tern#Complete
        au FileType python setl omnifunc=pythoncomplete#Complete
        au FileType xml setl omnifunc=xmlcomplete#CompleteTags
    aug END


""vim airline
"let g:airline#extensions#tabline#enabled = 1
"let g:airline_powerline_fonts = 1
"let g:airline_powerline_fonts = 1

"if !exists('g:airline_symbols')
        "let g:airline_symbols = {}
    "endif

"" unicode symbols
"let g:airline_left_sep = '»'
"let g:airline_left_sep = '▶'
"let g:airline_right_sep = '«'
"let g:airline_right_sep = '◀'
"let g:airline_symbols.linenr = '␊'
"let g:airline_symbols.linenr = '␤'
"let g:airline_symbols.linenr = '¶'
"let g:airline_symbols.branch = '⎇'
"let g:airline_symbols.paste = 'ρ'
"let g:airline_symbols.paste = 'Þ'
"let g:airline_symbols.paste = '∥'
"let g:airline_symbols.whitespace = 'Ξ'

"" airline symbols
"let g:airline_left_sep = ''
"let g:airline_left_alt_sep = ''
"let g:airline_right_sep = ''
"let g:airline_right_alt_sep = ''
"let g:airline_symbols.branch = ''
"let g:airline_symbols.readonly = ''
"let g:airline_symbols.linenr = ''

let g:pyclewn_terminal = "xterm, -e"
