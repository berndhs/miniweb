
%define miniweb_ver 0.2
%define miniweb_dir miniweb-0.2.0

Name:    miniweb
Version: 0.2.0
Release: 1
Summary: A browser tool which uses different User Agents and screen sizes to test mobile versions of websites

License: GPLv3
Group:   Applications/Network
Packager: Bernd Stramm <bernd.stramm@gmail.com>
Url:     http://bernd-stramm.com/
Source: miniweb-0.2.0.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

# TODO: patches (?)


#Obsoletes:
#Provides: 
%if 0%{?fedora_version} || 0%{?rhel_version} || 0%{?centos_version}
BuildRequires:  qt4-devel
BuildRequires:  gcc-c++
%endif

%if 0%{?suse_version}
BuildRequires: libqt4-devel
BuildRequires: libQtWebKit-devel
BuildRequires: gcc-c++
%endif
%if 0%{?mandriva_version}
BuildRequires: qt4-devel
BuildRequires: gcc-c++
%endif

%description
A webkit-based browser tool which uses different User Agents and screen sizes to test mobile versions of websites.


%prep
%setup

%build
sh configure
make 

%install

rm -rf $RPM_BUILD_ROOT
install -p -d $RPM_BUILD_ROOT%{_bindir}
install -p -m 755 miniweb $RPM_BUILD_ROOT%{_bindir}

%clean
rm -rf %{buildroot}


%post 

%postun 


%files
%defattr(-,root,root,-)
%doc README
%doc COPYRIGHT
%doc LICENSE.txt
%doc helpman.html
%{_bindir}/miniweb

%changelog

* Wed Apr 23 2010 Bernd Stramm <bernd.stramm@gmail.com> - 0.2.0-1
- Initial RPM release




