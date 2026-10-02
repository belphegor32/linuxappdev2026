Name:           show
Version:        1.0
Release:        alt1
Group:          Other
License:        MIT
Source:         %name-%version.tar.gz
Summary:        Simple ncurses file viewer

BuildRequires:  libncursesw-devel

%description
Simple ncurses file viewer.

%prep
%setup -c

%build
make

%install
make install DESTDIR=%buildroot

%files
%_bindir/Show