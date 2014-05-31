%define major 0
%define minor 6
%define patchlevel 70

Name:           libslp-tapi
Version:        %{major}.%{minor}.%{patchlevel}
Release:        2
License:        Apache
Summary:        Telephony dbus client library
Group:          System/Libraries
Source0:        libslp-tapi-%{version}.tar.gz
BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(glib-2.0)
%if %{_repository}=="mobile"
BuildRequires:  pkgconfig(gobject-2.0)
%endif
BuildRequires:  pkgconfig(security-server)
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description
Telephony client API library

%package devel
Summary:        Telephony client API (devel)
Group:          Development/Libraries
Requires:       %{name} = %{version}

%description devel
Telephony client API library (devel)

%prep
%setup -q

%build
%if %{_repository}=="mobile"
cd mobile
%cmake .
make %{?jobs:-j%jobs}
%elseif %{_repository}=="wearable"
export LDFLAGS+=" -Wl,-z,nodelete "

%if 0%{?tizen_build_binary_release_type_eng}
export CFLAGS="$CFLAGS -DTIZEN_ENGINEER_MODE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_ENGINEER_MODE"
export FFLAGS="$FFLAGS -DTIZEN_ENGINEER_MODE"
%endif
%if 0%{?sec_build_binary_debug_enable}
export CFLAGS="$CFLAGS -DTIZEN_DEBUG_ENABLE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_DEBUG_ENABLE"
export FFLAGS="$FFLAGS -DTIZEN_DEBUG_ENABLE"
%endif
cd wearable
cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix} \
%if 0%{?tizen_build_binary_release_type_eng}
	-DTIZEN_ENGINEER_MODE=1 \
%endif

make %{?_smp_mflags}
%endif

%install
rm -rf %{buildroot}
%if %{_repository}=="wearable"
cd wearable
%elseif %{_repository}=="mobile"
cd mobile
%endif
%make_install

rm -rf %{buildroot}%{_includedir}/telephony/tapi/.gitignore
mkdir -p %{buildroot}%{_datadir}/license
%if %{_repository}=="mobile"
cp LICENSE %{buildroot}/usr/share/license/%{name}
%endif

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%if %{_repository}=="wearable"
%manifest wearable/libslp-tapi.manifest
%elseif %{_repository}=="mobile"
%manifest mobile/libslp-tapi.manifest
%endif
%defattr(-,root,root,-)
%{_libdir}/*.so.*
%if %{_repository}=="wearable"
%if 0%{?tizen_build_binary_release_type_eng}
%{_bindir}/tapitest
%endif
%{_datadir}/license/libslp-tapi
%elseif %{_repository}=="mobile"
/usr/share/license/%{name}
%endif

%files devel
%defattr(-,root,root,-)
%{_includedir}/telephony-client/*.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/*.so
