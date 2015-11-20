Pod::Spec.new do |s|
  s.name                   = "TriceKit"
  s.version                = "0.5.5"
  s.summary                = "The TriceKit iOS SDK does things."
  s.homepage               = "http://tricekit.com/"
  s.license                = { :type => 'none', :text => "Copyright 2015 STQRY" }
  s.author                 = { "Jake" => "jake.bellamy@stqry.com" }
  s.platform               = :ios, '7.0'
  s.source                 = { :git => "https://github.com/stqry/TriceKit.git", :tag => s.version }
  s.requires_arc           = true
  s.pod_target_xcconfig    = { 'OTHER_LDFLAGS' => '-lObjC -lc++' }
  s.source_files           = 'include/TriceKit.{h,m}'

  s.subspec 'Core' do |ss|
    ss.source_files = 'include/TriceKitShared/*.{h,m}'
    ss.vendored_libraries  = 'libTriceKitShared.a'

    ss.dependency 'AFNetworking/NSURLSession', '~> 2.5'
    ss.dependency 'Mantle', '~> 1.5'
  end

  s.subspec 'ZTA' do |ss|
    ss.source_files = 'include/TriceKitZTA/*.{h,m}'
    ss.vendored_libraries  = 'libTriceKitZTA.a'

    ss.dependency 'TriceKit/Core'
  end

  s.subspec 'Mapping' do |ss|

    ss.source_files = 'include/TriceKitMapping/*.{h,m}'
    ss.vendored_libraries  = 'libTriceKitMapping.a'

    ss.dependency 'TriceKit/Core'
    ss.dependency 'BFPaperView', '~> 2.1'
    ss.dependency 'BFPaperButton', '~> 2.0'
    ss.dependency 'Masonry', '~> 0.6'
    ss.dependency 'PocketSVG', '~> 0.6'
    ss.dependency 'SDWebImage', '~> 3.7'
  end

end
